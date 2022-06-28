#pragma once

#include "Hittable.h"
#include "Isotropic.h"

struct Ray;
struct HitRecord;
struct AABB;
struct Material;
struct ITexture;
struct Color;

struct ConstantMedium : Hittable {
	std::shared_ptr<Hittable> Boundary;
	std::shared_ptr<Material> PhaseFunction;
	float NegInverseDensity{ 0.0f };

	ConstantMedium(std::shared_ptr<Hittable> boundary, float density, std::shared_ptr<ITexture> texture)
		: Boundary(boundary),
		NegInverseDensity(-1.0f / density),
		PhaseFunction(std::make_shared<Isotropic>(texture)) { }

	ConstantMedium(std::shared_ptr<Hittable> boundary, float density, Color color)
		: Boundary(boundary),
		NegInverseDensity(-1.0f / density),
		PhaseFunction(std::make_shared<Isotropic>(color)) { }

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

	virtual bool BoundingBox(float time0, float time1, AABB& aabbOut) const override {
		return Boundary->BoundingBox(time0, time1, aabbOut);
	}
};