#pragma once

#include <memory>
#include <iostream>
#include "RTWeekend.h"
#include "AABB.h"

struct Ray;
struct HitRecord;

struct Hittable {
    virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const = 0;

    virtual bool BoundingBox(float time0, float time1, AABB& aabbOut) const = 0;

    static bool BoxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, Axis axis) {
        AABB boxA, boxB;

        if (!a->BoundingBox(0.0f, 0.0f, boxA) || !b->BoundingBox(0.0f, 0.0f, boxB)) {
            std::cerr << "No bounding box to compare.\n";
        }

        return boxA.Minimum[axis] < boxB.Minimum[axis];
    }

    static bool BoxCompareX(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
        return BoxCompare(a, b, Axis::X);
    }

    static bool BoxCompareY(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
        return BoxCompare(a, b, Axis::Y);
    }

    static bool BoxCompareZ(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b) {
        return BoxCompare(a, b, Axis::Z);
    }
};
