#pragma once

#include <memory>
#include "IHittable.h"
#include "Vec3.h"

struct Ray;
struct HitRecord;
struct IMaterial;

struct Sphere : IHittable {
    Vec3 Center;
    float Radius;
    std::shared_ptr<IMaterial> Material;

    Sphere() : Center(Vec3()), Radius(0.0f) { }

    Sphere(const Vec3& center, float radius, std::shared_ptr<IMaterial> material)
        : Center(center), Radius(radius), Material(material) { }

    bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;
};
