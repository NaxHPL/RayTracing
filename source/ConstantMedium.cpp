#include <cmath>
#include "ConstantMedium.h"
#include "Ray.h"
#include "HitRecord.h"
#include "RTWeekend.h"

bool ConstantMedium::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
    HitRecord hitEnter, hitExit;

    if (!Boundary->Hit(ray, -INF_F, INF_F, hitEnter)) {
        return false;
    }

    if (!Boundary->Hit(ray, hitEnter.T + 0.0001f, INF_F, hitExit)) {
        return false;
    }

    if (hitEnter.T < tMin) {
        hitEnter.T = tMin;
    }

    if (hitExit.T > tMax) {
        hitExit.T = tMax;
    }

    if (hitEnter.T >= hitExit.T) {
        return false;
    }

    if (hitEnter.T < 0.0f) {
        hitEnter.T = 0.0f;
    }

    const float rayLength = ray.Direction.Magnitude();
    const float distanceInsideBoundary = (hitExit.T - hitEnter.T) * rayLength;
    const float hitDistance = NegInverseDensity * std::logf(RandomFloat());

    if (hitDistance > distanceInsideBoundary) {
        return false;
    }

    hitRecord.T = hitEnter.T + hitDistance / rayLength;
    hitRecord.Point = ray.At(hitRecord.T);
    hitRecord.Normal = Vec3::Right(); // arbitrary
    hitRecord.FrontFace = true; // arbitrary
    hitRecord.Material = PhaseFunction;

    return true;
}