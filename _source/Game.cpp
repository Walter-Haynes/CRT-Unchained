#include "Game.h"

void Game::Run()
{
	if (!glfwInit()) return;

	CreateWindow();

	Start();
	while (!glfwWindowShouldClose(window_))
	{
		Update();
	}
	Stop();

	glfwDestroyWindow(window_);
	
	glfwTerminate();
}

void Game::Start()
{
	world_.Add(new Sphere(float3(0.0f, 0.0f, 2.0f), 0.5f));

	world_.Add(new Sphere(float3(0.225f, 0.15f, 1.5f), 0.20f));
	world_.Add(new Sphere(float3(-0.225f, 0.15f, 1.5f), 0.20f));

	world_.Add(new Sphere(float3(1.5f, 1.5f, 4.0f), 0.5f));

	world_.Add(new Sphere(float3(-0.5f, 0.75f, 1.0f), 0.5f));
	
	world_.Add(new Sphere(float3(0.0f, -100.5f, 0.0f), 100.0f));
	//world.Add(new Plane(float3::zero, float3::up));

	camera_.CalculatePositions();
}

void Game::Update()
{
	Draw();
}

void Game::Stop()
{
	//destroy world
}


void Game::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for(int x = 0; x < screen_width; x++)
	{
		for(int y = 0; y < screen_height; y++)
		{
			Colour colour = Colour(0, 0, 0, 0);

			for (int i = 0; i < samples_per_pixel; i++)
			{
				const float u = static_cast<float>(x + random_range(-1, 1)) / screen_width;
				const float v = static_cast<float>(y + random_range(-1, 1)) / screen_height;

				Ray3D ray = camera_.get_ray(u, v);

				colour += Trace(ray, 0);
			}

			//Average colour, then gamma correct.
			colour /= samples_per_pixel;
			colour.GammaCorrect();
			
			DrawPixel(x, y, colour);
		}
	}

	glfwSwapBuffers(window_);
}

Colour Game::Trace(Ray3D& ray, int bounces)
{
	HitInfo hitInfo = HitInfo();

	//Exit recursion after max bounces.
	if (bounces >= max_bounces) return {0, 0, 0};

	float min_range = FLT_EPSILON;
	float max_range = FLT_MAX;

	//If hits, scatter
	if (world_.Intersect(ray, hitInfo, min_range, max_range))
	{
		const dir3 target = hitInfo.normal + random_direction();
		Ray3D new_ray = Ray3D(hitInfo.position, target);

		const Colour colour = Trace(new_ray, bounces++);

		return (colour / 2.0);
	}

	//Sky colour
	const float t = (ray.direction.y + 1);
	return lerp(sky_colour_, void_colour_, t);
}

//Based on Raylib's DrawPixel method.
void Game::DrawPixel(const int x, const int y, const Colour colour)
{
	glPointSize(2);
	
	glBegin(GL_POINTS);
		glColor4f(
			clamp(colour.r, 0.0f, 0.99f), 
			clamp(colour.g, 0.0f, 0.99f),
			clamp(colour.b, 0.0f, 0.99f),
			clamp(colour.a, 0.0f, 0.99f));
		glVertex2i(x, y);
	glEnd();
}

void Game::CreateWindow()
{
	window_ = glfwCreateWindow(screen_width, screen_height, "3D Ray-Tracing", nullptr, nullptr);

	if (!window_)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window_);

	glViewport(0.0f, 0.0f, screen_width, screen_height);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, screen_width, 0, screen_height, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
