#pragma once

#include <GLFW/glfw3.h>

#include "Singleton.h"
#include "RayTraceCamera.h"
#include "MathUtils.h"

#include "GameSettings.h"
#include "World.h"

#include "Colour.h"

class Game : public Singleton<Game>
{
public:
	void Run();

private:
	void Start();
	void Update();
	void Stop();

	void Draw();

	Colour Trace(Ray3D& ray, int bounces);

	static void DrawPixel(int x, int y, Colour colour);

	void CreateWindow();

public:
	const static int screen_height = 128;
	const static int screen_width = (screen_height * aspect_ratio);

	const static int samples_per_pixel = 32;

	const static int max_bounces = 32;

private:
	RayTraceCamera camera_ = RayTraceCamera();

	World world_ = World();

	GLFWwindow* window_ = nullptr;

	Colour sky_colour_ = Colour(1, 1, 1, 1);
	Colour void_colour_ = Colour(0.4f, 0.75f, 1.0f, 1);
};
