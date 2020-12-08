#include "Colour.h"

Colour Colour::operator+(const Colour& other) const
{
	return {
		(this->r + other.r),
		(this->g + other.g),
		(this->b + other.b),
		(this->a + other.a)};
}

Colour Colour::operator-(const Colour& other) const
{
	return {
		(this->r - other.r),
		(this->g - other.g),
		(this->b - other.b),
		(this->a - other.a)};
}

Colour Colour::operator*(const float value) const
{
	return {
		(this->r * value),
		(this->g * value),
		(this->b * value),
		(this->a * value)};
}

Colour Colour::operator/(const float value) const
{
	return {
		(this->r / value),
		(this->g / value),
		(this->b / value),
		(this->a / value)};
}

Colour& Colour::operator+=(const Colour& other)
{
	this->r += other.r;
	this->g += other.g;
	this->b += other.b;
	this->a += other.a;

	return *this;
}

Colour& Colour::operator-=(const Colour& other)
{
	this->r -= other.r;
	this->g -= other.g;
	this->b -= other.b;
	this->a -= other.a;

	return *this;
}

Colour& Colour::operator*=(const float value)
{
	this->r *= value;
	this->g *= value;
	this->b *= value;
	this->a *= value;

	return *this;
}

Colour& Colour::operator/=(const float value)
{
	this->r /= value;
	this->g /= value;
	this->b /= value;
	this->a /= value;

	return *this;
}

Colour& Colour::GammaCorrect()
{
	this->r = sqrtf(this->r);
	this->g = sqrtf(this->g);
	this->b = sqrtf(this->b);
	
	return *this;
}
