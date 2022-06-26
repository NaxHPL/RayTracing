#pragma once

#include "Hittable.h"
#include "AABB.h"
#include "RTWeekend.h"
#include "Vec3.h"

struct Ray;
struct HitRecord;

struct Rotation : Hittable {
	std::shared_ptr<Hittable> Object;
	float CosTheta{ 0.0f };
	float SinTheta{ 0.0f };
	bool HasBox{ false };
	AABB BBox;

	void Init(std::shared_ptr<Hittable> hittable, float angle);

	virtual Vec3 Rotate(float x, float y, float z) const = 0;

	Vec3 Rotate(const Vec3& v) const { return Rotate(v.X, v.Y, v.Z); }

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

	virtual bool BoundingBox(float time0, float time1, AABB& aabbOut) const override {
		aabbOut = BBox;
		return HasBox;
	}
};

struct RotateX : Rotation {
	RotateX(std::shared_ptr<Hittable> hittable, float angle) { Init(hittable, angle); }

	virtual Vec3 Rotate(float x, float y, float z) const override {
		return Vec3(
			x,
			CosTheta * y - SinTheta * z,
			SinTheta * y + CosTheta * z
		);
	}
};

struct RotateY : Rotation {
	RotateY(std::shared_ptr<Hittable> hittable, float angle) { Init(hittable, angle); }

	virtual Vec3 Rotate(float x, float y, float z) const override {
		return Vec3(
			CosTheta * x + SinTheta * z,
			y,
			-SinTheta * x + CosTheta * z
		);
	}
};

struct RotateZ : Rotation {
	RotateZ(std::shared_ptr<Hittable> hittable, float angle) { Init(hittable, angle); }

	virtual Vec3 Rotate(float x, float y, float z) const override {
		return Vec3(
			CosTheta * x - SinTheta * y,
			SinTheta * x + CosTheta * y,
			z
		);
	}
};

//struct RotateX : Hittable {
//	std::shared_ptr<Hittable> Object;
//	float CosTheta{ 0.0f };
//	float SinTheta{ 0.0f };
//	bool HasBox{ false };
//	AABB BBox;
//
//	RotateX(std::shared_ptr<Hittable> hittable, float angle);
//
//	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
//
//	virtual bool BoundingBox(float time0, float time1, AABB& aabbOut) const override {
//		aabbOut = BBox;
//		return HasBox;
//	}
//};
//
//struct RotateY : Hittable {
//	std::shared_ptr<Hittable> Object;
//	float CosTheta{ 0.0f };
//	float SinTheta{ 0.0f };
//	bool HasBox{ false };
//	AABB BBox;
//
//	RotateY(std::shared_ptr<Hittable> hittable, float angle);
//
//	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
//
//	virtual bool BoundingBox(float time0, float time1, AABB& aabbOut) const override {
//		aabbOut = BBox;
//		return HasBox;
//	}
//};
//
//struct RotateZ : Hittable {
//	std::shared_ptr<Hittable> Object;
//	float CosTheta{ 0.0f };
//	float SinTheta{ 0.0f };
//	bool HasBox{ false };
//	AABB BBox;
//
//	RotateZ(std::shared_ptr<Hittable> hittable, float angle);
//
//	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
//
//	virtual bool BoundingBox(float time0, float time1, AABB& aabbOut) const override {
//		aabbOut = BBox;
//		return HasBox;
//	}
//};