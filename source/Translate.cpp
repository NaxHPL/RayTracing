#include "Translate.h"
#include "Ray.h"
#include "HitRecord.h"
#include "AABB.h"

bool Translate::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
    Ray movedRay(ray.Origin - Translation, ray.Direction, ray.Time);

    if (!Object->Hit(movedRay, tMin, tMax, hitRecord)) {
        return false;
    }

    hitRecord.Point += Translation;
    hitRecord.SetFaceNormal(movedRay.Direction, hitRecord.Normal);

    return true;
}

bool Translate::BoundingBox(float time0, float time1, AABB& aabbOut) const {
    if (!Object->BoundingBox(time0, time1, aabbOut)) {
        return false;
    }

    aabbOut = AABB(
        aabbOut.Minimum + Translation,
        aabbOut.Maximum + Translation
    );

    return true;
}
