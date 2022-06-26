#pragma once

#include "Hittable.h"
#include "Vec3.h"

struct Ray;
struct HitRecord;
struct AABB;

struct Translate : Hittable {

	std::shared_ptr<Hittable> Object;
	Vec3 Translation;

	Translate(std::shared_ptr<Hittable> hittable, const Vec3& translation)
		: Object(hittable), Translation(translation) { }

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

	virtual bool BoundingBox(float time0, float time1, AABB& aabbOut) const override;
};