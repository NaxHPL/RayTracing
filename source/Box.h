#pragma once

#include "Hittable.h"
#include "Vec3.h"
#include "HittableCollection.h"
#include "AABB.h"

struct Material;
struct Ray;
struct HitRecord;

struct Box : Hittable {

	Vec3 Min;
	Vec3 Max;
	HittableCollection Sides;

	Box() { }

	Box(const Vec3& min, const Vec3& max, std::shared_ptr<Material> mat);

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

	virtual bool BoundingBox(float time0, float time1, AABB& aabbOut) const {
		aabbOut = AABB(Min, Max);
		return true;
	}
};