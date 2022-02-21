#include <memory>
#include <vector>
#include "HittableCollection.h"
#include "IHittable.h"
#include "HitRecord.h"

struct Ray;

bool HittableCollection::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
    bool hitAnything = false;
    HitRecord tempRecord;

    for (const std::shared_ptr<IHittable> hittable : hittables) {
        if (hittable->Hit(ray, tMin, tMax, tempRecord)) {
            hitAnything = true;
            tMax = tempRecord.T;
            hitRecord = tempRecord;
        }
    }

    return hitAnything;
}