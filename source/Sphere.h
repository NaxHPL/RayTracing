#pragma once

#include <memory>
#include "Hittable.h"
#include "Vec3.h"

struct Ray;
struct HitRecord;
struct IMaterial;

struct Sphere : Hittable {
    Vec3 Center;
    float Radius{ 0.0f };
    std::shared_ptr<IMaterial> Material;

    Sphere() {}

    Sphere(const Vec3& center, float radius, std::shared_ptr<IMaterial> material)
        : Center(center), Radius(radius), Material(material) {}

    bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

    bool BoundingBox(float time0, float time1, AABB& aabbOut) const override;
};
