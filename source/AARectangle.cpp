#include "AARectangle.h"
#include "Ray.h"
#include "HitRecord.h"
#include "Vec3.h"
#include "AABB.h"

bool AARectangle::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
    Axis kAxis = GetAxisK();
    float t = (K - ray.Origin[kAxis]) / ray.Direction[kAxis];

    if (t < tMin || t > tMax) {
        return false;
    }

    Axis iAxis = GetAxisI();
    Axis jAxis = GetAxisJ();
    float pI = ray.Origin[iAxis] + t * ray.Direction[iAxis];
    float pJ = ray.Origin[jAxis] + t * ray.Direction[jAxis];

    if (pI < I0 || pI > I1 || pJ < J0 || pJ > J1) {
        return false;
    }

    hitRecord.T = t;
    hitRecord.Point = ray.At(t);
    hitRecord.U = (pI - I0) / (I1 - I0);
    hitRecord.V = (pJ - J0) / (J1 - J0);
    hitRecord.Material = Mat;
    hitRecord.SetFaceNormal(ray.Direction, GetOutwardNormal());

    return true;
}

bool AARectangle::BoundingBox(float time0, float time1, AABB& aabbOut) const {
    // The bounding box must have non-zero width in every dimension
    const float kPadding = 0.0001f;

    Axis iAxis = GetAxisI();
    Axis jAxis = GetAxisJ();
    Axis kAxis = GetAxisK();

    Vec3 min;
    min[iAxis] = I0;
    min[jAxis] = J0;
    min[kAxis] = K - kPadding;

    Vec3 max;
    max[iAxis] = I1;
    max[jAxis] = J1;
    max[kAxis] = K + kPadding;

    aabbOut = AABB(min, max);
    return true;
}