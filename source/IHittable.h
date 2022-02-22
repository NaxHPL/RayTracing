#pragma once

struct Ray;
struct HitRecord;
struct AABB;

struct IHittable {
    virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const = 0;

    virtual bool BoundingBox(float time0, float time1, AABB& aabbOut) const = 0;
};
