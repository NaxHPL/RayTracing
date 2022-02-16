#pragma once

#include "IHittable.h"
#include "Vec3.h"

struct Ray;
struct HitRecord;

struct Sphere : IHittable {
    Vec3 Center;
    float Radius;

    Sphere() : Center(Vec3()), Radius(0.0f) { }

    Sphere(const Vec3& center, float radius) : Center(center), Radius(radius) { }

    bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
};
