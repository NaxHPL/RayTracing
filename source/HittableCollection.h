#pragma once

#include <memory>
#include <vector>
#include "Hittable.h"

struct Ray;
struct HitRecord;
struct AABB;

struct HittableCollection : Hittable {
    std::vector<std::shared_ptr<Hittable>> Hittables;

    HittableCollection() {}

    HittableCollection(const std::shared_ptr<Hittable> hittable) {
        Add(hittable);
    }

    void Clear() {
        Hittables.clear();
    }

    void Add(std::shared_ptr<Hittable> hittable) {
        Hittables.push_back(hittable);
    }

    bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

    bool BoundingBox(float time0, float time1, AABB& aabbOut) const override;
};
