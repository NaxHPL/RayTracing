#pragma once

#include <memory>
#include <vector>
#include "IHittable.h"

struct Ray;
struct HitRecord;
struct AABB;

struct HittableCollection : IHittable {
    std::vector<std::shared_ptr<IHittable>> Hittables;

    void Clear() {
        Hittables.clear();
    }

    void Add(std::shared_ptr<IHittable> hittable) {
        Hittables.push_back(hittable);
    }

    bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

    bool BoundingBox(float time0, float time1, AABB& aabbOut) const override;
};
