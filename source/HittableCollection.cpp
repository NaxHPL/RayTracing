#include <memory>
#include <vector>
#include "HittableCollection.h"
#include "Hittable.h"
#include "HitRecord.h"
#include "AABB.h"

struct Ray;

bool HittableCollection::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
    bool hitAnything = false;
    HitRecord tempRecord;

    for (size_t i = 0; i < Hittables.size(); i++) {
        if (Hittables[i]->Hit(ray, tMin, tMax, tempRecord)) {
            hitAnything = true;
            tMax = tempRecord.T;
            hitRecord = tempRecord;
        }
    }

    return hitAnything;
}

bool HittableCollection::BoundingBox(float time0, float time1, AABB& aabbOut) const {
    if (Hittables.empty()) {
        return false;
    }

    if (Hittables[0]->BoundingBox(time0, time1, aabbOut)) {
        return false;
    }

    AABB aabbTmp;

    for (size_t i = 1; i < Hittables.size(); i++) {
        if (!Hittables[i]->BoundingBox(time0, time1, aabbTmp)) {
            return false;
        }

        AABB::SurroundingBox(aabbOut, aabbTmp, aabbOut);
    }

    return true;
}
