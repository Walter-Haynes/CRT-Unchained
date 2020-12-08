#include "MathUtils.h"

#pragma region Float3

const float3 float3::zero(0.0f, 0.0f, 0.0f);
const float3 float3::one(1.0f, 1.0f, 1.0f);

const float3 float3::left(1.0f, 0.0f, 0.0f);
const float3 float3::right(-1.0f, 0.0f, 0.0f);

const float3 float3::up(0.0f, 1.0f, 0.0f);
const float3 float3::down(0.0f, -1.0f, 0.0f);

const float3 float3::forward(0.0f, 0.0f, 1.0f);
const float3 float3::backward(0.0f, 0.0f, -1.0f);

#pragma region Arithmathic_Operators

float3 float3::operator +(const float3& other) const
{
	return float3(this->x + other.x, this->y + other.y, this->z + other.z);
}

float3 float3::operator -(const float3& other) const
{
	return float3(this->x - other.x, this->y - other.y, this->z - other.z);
}

float3 float3::operator *(const float3& other) const
{
	return float3(this->x * other.x, this->y * other.y, this->z * other.z);
}

float3 float3::operator *(const float value) const
{
	return float3(this->x * value, this->y * value, this->z * value);
}

float3 float3::operator /(const float3& other) const
{
	return float3(this->x / other.x, this->y / other.y, this->z / other.z);
}

float3 float3::operator /(const float value) const
{
	return float3(this->x / value, this->y / value, this->z / value);
}

#pragma endregion Arithmathic_Operators

#pragma region Compound_Operators

float3& float3::operator +=(const float3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

float3& float3::operator -=(const float3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;

	return *this;
}

float3& float3::operator *=(const float3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;

	return *this;
}

float3& float3::operator *=(const float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;

	return *this;
}

float3& float3::operator /=(const float3& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;

	return *this;
}

float3& float3::operator /=(const float value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;

	return *this;
}

#pragma endregion Arithmathic_Operators

//Assignment
float3& float3::operator =(const float3& other) = default;

/*float3& float3::operator = (const float3 &other)
{
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;

    return *this;
}*/

#pragma region Equality_Operators

bool float3::operator ==(const float3& other) const
{
	return (equals(this->x, other.x) &&
		equals(this->y, other.y) &&
		equals(this->z, other.z));
}

bool float3::operator !=(const float3& other) const
{
	return (equals(this->x, other.x) ||
		equals(this->y, other.y) ||
		equals(this->z, other.z));
}

#pragma endregion Equality_Operators

float float3::sqrLength() const
{
	return (x * x + y * y + z * z);
}

float float3::length() const
{
	return sqrt(sqrLength());
}

float float3::dot(const float3& other) const
{
	return (this->x * other.x) +
		(this->y * other.y) +
		(this->z * other.z);
}

float3 float3::cross(const float3& other) const
{
	return float3(this->y * other.z - this->z,
	              this->z * other.x - this->x,
	              this->x * other.y - this->y);
}

float3 float3::normalized() const
{
	float length = this->length();
	if (length > EPSILON)
	{
		return (*this / length);
	}
	else
	{
		return float3::zero;
	}
}

float3& float3::normalize()
{
	float length = this->length();
	if (length > EPSILON)
	{
		return (*this /= length);
	}
	else
	{
		return (*this = float3::zero);
	}
}

float3 float3::lerp(const float3& current, const float3& target, const float t)
{
	float x = lerp_f(current.x, target.x, t);
	float y = lerp_f(current.y, target.y, t);
	float z = lerp_f(current.z, target.z, t);

	return float3(x, y, z);
}

std::ostream& operator<<(std::ostream& ostream, const float3& subject)
{
	ostream << "(";
	ostream << subject.x << ",";
	ostream << subject.y << ",";
	ostream << subject.z;
	ostream << ")";

	return ostream;
}

#pragma endregion Float3

#pragma region Ray3D

Ray3D::Ray3D() = default;

Ray3D::Ray3D(const pos3& origin, const dir3& direction, const float length)
{
	this->origin = origin;
	this->direction = direction.normalized(); //normalize in here, just to be safe.
	this->length = length;
}

float3 Ray3D::position_at(const float scalar) const
{
	return origin + (direction * abs(scalar));
}

#pragma endregion Ray

#pragma region HitInfo

HitInfo::HitInfo()
{
	this->position = float3::zero;
	this->normal = float3::up;
	this->t = -1;
}

HitInfo::HitInfo(const pos3& position, const dir3& normal, const float t)
{
	this->position = position;
	this->normal = normal;
	this->t = t;
}

#pragma endregion HitInfo

#pragma region Shapes

#pragma region Plane

Plane::Plane()
{
	position = float3::zero;
	normal = float3::up;
}

Plane::Plane(const pos3 position, const dir3 normal)
{
	this->position = position;
	this->normal = normal;
}

bool Plane::Intersect(Ray3D& ray, HitInfo& hitInfo, float& min, float& max)
{
	float3 dir = (this->position - ray.origin); //camera_to_plane_dir

	float denominator = normal.dot(ray.direction);
	if (abs(denominator) > EPSILON) //If the normal is in the opposing direction as the ray..
	{
		float t = dir.dot(normal) / denominator;

		if (t > 0)
		{
			float3 pos = ray.position_at(t);

			return true;
		}
	}

	return false;
}

#pragma endregion Plane

#pragma region Sphere

Sphere::Sphere()
{
	this->position = float3::zero;
	this->radius = 1.0f;
}

Sphere::Sphere(const pos3 position, const float radius)
{
	this->position = position;
	this->radius = radius;
}

//Stole this intersect method from RayTracingInOneWeekend.
bool Sphere::Intersect(Ray3D& ray, HitInfo& hitInfo, float& min, float& max)
{
	const float3 oc = (ray.origin - this->position); //P - C
	const float a = ray.direction.sqrLength();
	const float b = dot(ray.direction, oc);
	const float c = oc.sqrLength() - radius * radius;

	const float discriminant = b*b - a*c;
	if (discriminant > 0)
	{
		//sqrt(discriminant) = distance to edge of sphere.
		float t = (-b - sqrt(discriminant)) / a;
		if (t < max && t > min)
		{
			hitInfo.t = t;
			hitInfo.position = ray.position_at(t); //Where the ray hit it.
			hitInfo.normal = (hitInfo.position - this->position) / radius;
			return true;
		}

		t = (-b + sqrt(discriminant)) / a;
		if (t < max && t > min)
		{
			hitInfo.t = t;
			hitInfo.position = ray.position_at(t);
			hitInfo.normal = (hitInfo.position - this->position) / radius;
			return true;
		}
	}

	return false;
}

#pragma endregion Sphere

#pragma endregion Shapes