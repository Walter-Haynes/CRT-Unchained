#pragma once

#include "MathUtils.h"

struct Colour
{
	float r, g, b, a;

	Colour() : r(0), g(0), b(0), a(1)
	{
	}

	Colour(const float r, const float g, const float b, const float a = 1)
	{
		this->r = r;
		this->g = g;
		this->b = b;

		this->a = a;
	}

	Colour operator +(const Colour& other) const;
	Colour operator -(const Colour& other) const;

	Colour operator *(const float value) const;
	Colour operator /(const float value) const;

	Colour& operator +=(const Colour& other);
	Colour& operator -=(const Colour& other);

	Colour& operator *=(const float value);
	Colour& operator /=(const float value);

	Colour& GammaCorrect();


	//Implicitly converts to OpenGL's color4f class
	/*
	operator glColor4f()
	{
		return glColor4f(r, g, b, a);
	}
	*/
};

static Colour lerp(const Colour& current, const Colour& target, float t)
{
	float r = lerp_f(current.r, target.r, t);
	float g = lerp_f(current.g, target.g, t);
	float b = lerp_f(current.b, target.b, t);
	float a = lerp_f(current.a, target.a, t);

	return {r, g, b, a};
}
