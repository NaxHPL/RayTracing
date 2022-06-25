#pragma once

#include "Hittable.h"
#include "RTWeekend.h"
#include "Vec3.h"

struct AABB;
struct Ray;
struct HitRecord;
struct Material;

struct AARectangle : Hittable {
	
	std::shared_ptr<Material> Mat;
	float I0{ 0.0f };
	float I1{ 0.0f };
	float J0{ 0.0f };
	float J1{ 0.0f };
	float K{ 0.0f };

	AARectangle() { }

	AARectangle(float i0, float i1, float j0, float j1, float k, std::shared_ptr<Material> mat)
		: I0(i0), I1(i1), J0(j0), J1(j1), K(k), Mat(mat) { }

	virtual inline Axis GetAxisI() const = 0;
	virtual inline Axis GetAxisJ() const = 0;
	virtual inline Axis GetAxisK() const = 0;

	virtual inline Vec3 GetOutwardNormal() const = 0;

	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

	virtual bool BoundingBox(float time0, float time1, AABB& aabbOut) const override;
};

struct XYRectangle : AARectangle {

	XYRectangle() : AARectangle() { }

	XYRectangle(float x0, float x1, float y0, float y1, float k, std::shared_ptr<Material> mat)
		: AARectangle(x0, x1, y0, y1, k, mat) { }

	virtual inline Axis GetAxisI() const override { return Axis::X; }
	virtual inline Axis GetAxisJ() const override { return Axis::Y; }
	virtual inline Axis GetAxisK() const override { return Axis::Z; }

	virtual inline Vec3 GetOutwardNormal() const override { return -Vec3::Forward(); }
};

struct XZRectangle : AARectangle {

	XZRectangle() : AARectangle() { }

	XZRectangle(float x0, float x1, float z0, float z1, float k, std::shared_ptr<Material> mat)
		: AARectangle(x0, x1, z0, z1, k, mat) { }

	virtual inline Axis GetAxisI() const override { return Axis::X; }
	virtual inline Axis GetAxisJ() const override { return Axis::Z; }
	virtual inline Axis GetAxisK() const override { return Axis::Y; }

	virtual inline Vec3 GetOutwardNormal() const override { return Vec3::Up(); }
};

struct YZRectangle : AARectangle {

	YZRectangle() : AARectangle() { }

	YZRectangle(float y0, float y1, float z0, float z1, float k, std::shared_ptr<Material> mat)
		: AARectangle(y0, y1, z0, z1, k, mat) { }

	virtual inline Axis GetAxisI() const override { return Axis::Y; }
	virtual inline Axis GetAxisJ() const override { return Axis::Z; }
	virtual inline Axis GetAxisK() const override { return Axis::X; }

	virtual inline Vec3 GetOutwardNormal() const override { return -Vec3::Right(); }
};