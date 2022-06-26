#pragma once

#include "Hittable.h"
#include "AABB.h"

struct Ray;
struct HitRecord;

struct RotateY : Hittable {
	std::shared_ptr<Hittable> Object;
	float CosTheta{ 0.0f };
	float SinTheta{ 0.0f };
	bool HasBox{ false };
	AABB BBox;

	RotateY(std::shared_ptr<Hittable> hittable, float angle);

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

	virtual bool BoundingBox(float time0, float time1, AABB& aabbOut) const override {
		aabbOut = BBox;
		return HasBox;
	}
};