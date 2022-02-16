#pragma once

struct Ray;
struct HitRecord;

struct IHittable {
    virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const = 0;
};
