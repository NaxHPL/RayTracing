#pragma once

#include <memory>
#include "Hittable.h"
#include "Vec3.h"

struct Material;
struct Ray;
struct HitRecord;
struct AABB;

struct MovingSphere : Hittable {
    Vec3 Center0, Center1;
    float Time0{ 0.0f };
    float Time1{ 0.0f };
    float Radius{ 0.0f };
    std::shared_ptr<Material> Mat;

    MovingSphere() {}

    MovingSphere(Vec3 center0, Vec3 center1, float time0, float time1, float radius, std::shared_ptr<Material> material)
        : Center0(center0), Center1(center1), Time0(time0), Time1(time1), Radius(radius), Mat(material) {}

    bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

    Vec3 Center(float time) const;

    bool BoundingBox(float time0, float time1, AABB& aabbOut) const override;
};
