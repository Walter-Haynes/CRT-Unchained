#include "RayTraceCamera.h"

float3 RayTraceCamera::eye_position() const
{
	return position;
}

Ray3D RayTraceCamera::get_ray(const float u, const float v) const
{
	const float3 offset = float3((u * viewport_width_), (v * viewport_height_), 0);
	const point3 uv_world_pos = (viewport_bottom_left_ + offset);

	dir3 dir_to_pixel_world_pos = (uv_world_pos - eye_position());
	//TODO: Remove normalize from here.
	dir_to_pixel_world_pos.normalize(); // //No need to normalize, is will be done in Ray constructor. This is temporary

	return { uv_world_pos, dir_to_pixel_world_pos, 10000 };
}

void RayTraceCamera::CalculatePositions()
{
	viewport_center_ = CalculateViewportCenter();
	viewport_bottom_left_ = CalculateViewportBottomLeft();

	//std::cout << viewport_bottom_left << std::endl;
}


point3 RayTraceCamera::CalculateViewportCenter() const
{
	point3 center = eye_position() + viewport_offset;
	return center;
}

point3 RayTraceCamera::CalculateViewportBottomLeft() const
{
	const float3 offset = float3(-viewport_half_width_, -viewport_half_height_, 0);
	return viewport_center_ + offset;
}
