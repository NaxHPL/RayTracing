#pragma once

#include <memory>
#include <vector>
#include "Hittable.h"
#include "HittableCollection.h"
#include "AABB.h"

struct Ray;
struct HitRecord;

struct BVHNode : Hittable {
    std::shared_ptr<Hittable> LeftChild;
    std::shared_ptr<Hittable> RightChild;
    AABB Box;

    BVHNode() {}

    BVHNode(const HittableCollection& collection, float time0, float time1)
        : BVHNode(collection.Hittables, 0, collection.Hittables.size(), time0, time1) {}

    BVHNode(const std::vector<std::shared_ptr<Hittable>>& srcObjects,
            size_t start,
            size_t end,
            float time0,
            float time1);

    bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

    bool BoundingBox(float time0, float time1, AABB& aabbOut) const override;
};
