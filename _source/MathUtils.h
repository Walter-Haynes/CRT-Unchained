#pragma once

#include <cmath>

#include <iostream>

//Reflect

//Stole PI from here:
//https://stackoverflow.com/questions/9912151/math-constant-pi-value-in-c
//But since I'm using floats I'll use 6 decimal places
//constexpr auto PI = 3.141592f;
#define PIE 3.141592

/*!
 *  Use this to convert from Degrees to Radians.
 *  (PI / 180)
 */
constexpr float DEG_TO_RAD = (PIE / 180);
/*!
 *  Use this to convert from Radians to Degrees.
 *  (180 / PI)
 */
constexpr float RAD_TO_DEG = (180 / PIE);

constexpr float TAU = (2 * PIE);

constexpr float EPSILON = 0.000001f;

//get smallest
inline float min(const float a, const float b)
{
	return ((a < b) ? a : b);
}

//get largest
inline float max(const float a, const float b)
{
	return ((a > b) ? a : b);
}

//Not sure if I have to implement this myself, so I'll just leave this out until I'm told otherwise.
//Would be REALLY stupid if we can't use those either...
//I don't want to deal with edge cases like not being able to handle negative zero, thanks.
/*
inline float abs(const float value)
{
    return (value <= 0.0f) ? 0.0f - value : value;
}
inline int abs(const int val)
{
    return (value <= 0) ? 0 - value : value;
}
 */


/*!
 *  Returns the sign of a (float) number - aka whether the positive, negative, or zero
 *
 *      @return The sign of a number. (-1 / 0 / +1) as an integer.
 */
inline int sign(const float value)
{
	if (value > 0) return 1;
	if (value < 0) return -1;
	return 0;
}

inline float clamp(float value, const float min, const float max)
{
	if (value < min)
	{
		value = min;
	}
	else if (value > max)
	{
		value = max;
	}

	return value;
}

inline int clamp(int value, const int min, const int max)
{
	if (value < min)
	{
		value = min;
	}
	else if (value > max)
	{
		value = max;
	}

	return value;
}


/*!
 *  Checks if two floats are approximately the same.
 *
 *      @param [in] max_difference: (Optional) The maximum difference between the floats.
 *
 *      @return True if approximately the same. False if not.
 */
inline bool equals(float a, float b, const float max_difference = EPSILON)
{
	// Calculate the difference.
	const float diff = abs(a - b);

	a = abs(a);
	b = abs(b);

	const float largest = max(a, b);

	return (diff <= largest * max_difference);
}

/*!
 *  Returns true if the input float a is zero.
 *
 *      @param [in] a: the float which we're checking.
 *      @param [in] max_difference: optional parameter.
 *
 *      @return True if zero. False if not.
 */
inline bool is_zero(const float value, const float max_difference = EPSILON)
{
	return equals(value, 0, max_difference);
}

/*!
 *  Moves a value current towards target.
 *
 *      @param [in] current: The current value.
 *      @param [in] target: The value to move towards.
 *      @param [in] max_delta: The maximum change that should be applied to the value.
 */
inline float move_towards(const float current, const float target, const float max_delta)
{
	if (abs(target - current) <= max_delta)
	{
		return target;
	}

	return current + sign(target - current) * max_delta;
}

inline float lerp_f(const float current, const float target, const float t)
{
	return (current * (1.0 - t)) + (target * t);
}

#pragma region Random

/*
static float random_range(const float min, const float max)
{
    int* p;
    p = (float*)malloc(sizeof(float)); // (definition is lying under the code)
    int res = ((float)p % max) + min; // (definition is lying under the code)
}
*/

inline float random_range(const float min, const float max)
{
	return ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (max - min)) + min;
}

#pragma endregion Random

#pragma region Float2

#pragma endregion Float2

#pragma region Float3

//TODO: Calculate length ONCE

struct float3
{
	float x = 0, y = 0, z = 0;

#pragma region Constructors

	float3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	float3(const float x, const float y, const float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float3(const float3& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

#pragma endregion Constructors

#pragma region Constants

	const static float3 zero, one, left, right, up, down, forward, backward;

#pragma endregion Constants

#pragma region Arithmathic_Operators

	float3 operator +(const float3& other) const;

	float3 operator -(const float3& other) const;

	float3 operator *(const float3& other) const;
	float3 operator *(const float value) const;

	float3 operator /(const float3& other) const;
	float3 operator /(const float value) const;

#pragma endregion Arithmathic_Operators

#pragma region Compound_Operators

	float3& operator +=(const float3& other);

	float3& operator -=(const float3& other);

	float3& operator *=(const float3& other);
	float3& operator *=(const float value);

	float3& operator /=(const float3& other);
	float3& operator /=(const float value);

#pragma endregion Arithmathic_Operators

	float3& operator =(const float3& other);

#pragma region Equality_Operators

	bool operator ==(const float3& other) const;
	bool operator !=(const float3& other) const;

#pragma endregion Equality_Operators

	float3 operator -() const
	{
		return float3(-x, -y, -z);
	}

	//> maybe
	//>= maybe
	//< maybe
	//<= maybe

	//Returns Length squared
	float sqrLength() const;
	float length() const;

	float dot(const float3& other) const;

	//TODO
	//I didn't know how to implement a cross product, and found the examples I found very... *not* readable.
	//Came across this: https://developer.download.nvidia.com/cg/cross.html (pun intended)
	//And I think .yzx, .zxy, etc are a great idea, so I'll implement them later!
	float3 cross(const float3& other) const;

	//(D / ||D||)
	float3 normalized() const;
	float3& normalize();

	static float3 lerp(const float3& current, const float3& target, const float t);

	static float3 random(const float min, const float max)
	{
		return float3(random_range(min, max), random_range(min, max), random_range(min, max));
	}

	/*
	//Obsolete
	static float3 random_direction()
	{
		while (true)
		{
			float3 d = float3::random(-1, 1);
			if (d.sqrLength() >= 1) continue;
			return d.normalized();
		}
	}
	*/

	//float3 direction_to(const float3& other) const;

	//lerp / lerp_unclamped

	//project

	//reflect off normal/plane

	friend std::ostream& operator <<(std::ostream& ostream, const float3& subject);
};

using point3 = float3;
using vector3 = float3;

using pos3 = float3;
using dir3 = float3;


static float sqrLength(const float3& f)
{
	return f.sqrLength();
}

static float length(const float3& f)
{
	return f.length();
}

//A * B
static float dot(const float3& a, const float3& b)
{
	return a.dot(b);
}

//A x B
static float3 cross(const float3& a, const float3& b)
{
	return a.cross(b);
}

static dir3 direction_to(const point3& from, const point3& to)
{
	return (to - from).normalized();
}

inline pos3 random_in_unit_sphere()
{
	while (true)
	{
		float3 d = float3::random(-1, 1);
		if (d.sqrLength() >= 1) continue;
		
		return d;
	}
}

static dir3 random_direction()
{
	return random_in_unit_sphere().normalized();
}

//Stolen from Ray tracing in one weekend
inline float3 random_in_hemisphere(const dir3& normal)
{
	const float3 in_unit_sphere = random_in_unit_sphere();
	const bool is_in_normal_hemisphere = dot(in_unit_sphere, normal) > 0.0f;
	
	return is_in_normal_hemisphere
		? in_unit_sphere
		: -in_unit_sphere;
}

#pragma endregion Float3

#pragma region Float4

#pragma endregion Float4

#pragma region Ray

struct Ray3D
{
	float3 origin = float3::zero;
	float3 direction = float3::forward;
	float length{};

	Ray3D();
	Ray3D(const pos3& origin, const dir3& direction, const float length = 1);

	//p(t) = O + t*D
	float3 position_at(const float scalar) const;
};

struct HitInfo
{
	pos3 position;
	dir3 normal;
	float t;

	HitInfo();
	HitInfo(const pos3& position, const dir3& normal, const float t);
};

#pragma endregion Ray

#pragma region Shapes

struct Intersectable
{
	//, ref float tMin, ref float tMax
	virtual bool Intersect(Ray3D& ray, HitInfo& hitInfo, float& min, float& max) = 0;
};

//https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection
//point on plane = p * normal + distance_to_origin;
struct Plane : public Intersectable
{
	float3 position = float3::zero;
	float3 normal = float3::up;

	Plane();
	Plane(const pos3 position, const dir3 normal);

	bool Intersect(Ray3D& ray, HitInfo& hitInfo, float& min, float& max) override;
};

struct Sphere : public Intersectable
{
	float3 position = float3::zero;
	float radius = 1.0f;

	Sphere();
	Sphere(const pos3 position, const float radius);

	bool Intersect(Ray3D& ray, HitInfo& hitInfo, float& min, float& max) override;
};

//Quad

//Disc

//Cube

//Torus

#pragma endregion Shapes
