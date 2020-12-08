#pragma once

#include "MathUtils.h"

#include "GameSettings.h"

class RayTraceCamera
{
public:
	pos3 position = float3::zero;
	//dir3 direction = float3::forward; //Not yet needed.

	float3 viewport_offset = float3(0, 0, 1);

	Ray3D get_ray(const float u, const float v) const;

	void CalculatePositions();

private:
	float viewport_height_ = 1.0f;
	float viewport_width_ = (viewport_height_ * aspect_ratio);

	float viewport_half_width_  = (viewport_width_  / 2.0f);
	float viewport_half_height_ = (viewport_height_ / 2.0f);

	point3 viewport_center_;
	point3 viewport_bottom_left_;

	float3 eye_position() const;

	point3 CalculateViewportCenter() const;
	point3 CalculateViewportBottomLeft() const;
};
