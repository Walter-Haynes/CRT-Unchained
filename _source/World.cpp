#include "World.h"

bool World::Intersect(Ray3D& ray, HitInfo& hitInfo, float& min, float& max)
{
	HitInfo cachedInfo = HitInfo();
	hitInfo = cachedInfo;

	bool hitSomething = false;
	float closestSoFar = max;

	for (int i = 0; i < GetCount(); i++)
	{
		Intersectable* primitive = entities_[i];

		if (primitive->Intersect(ray, cachedInfo, min, closestSoFar))
		{
			hitSomething = true;

			closestSoFar = cachedInfo.t;
			hitInfo = cachedInfo;
		}
	}

	return hitSomething;
}
