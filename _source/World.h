#pragma once

#include "List.h"
#include "MathUtils.h"

class World : public Intersectable
{
private:
	List<Intersectable*> entities_;

public:
	World() = default;

	unsigned int GetCount() const
	{
		return entities_.Count();
	}

	void Add(Intersectable* primitive)
	{
		entities_.Add(primitive);
	}

	bool Intersect(Ray3D& ray, HitInfo& hitInfo, float& min, float& max) override;
};
