#include <cmath>
#include "MovingSphere.h"
#include "Vec3.h"
#include "Ray.h"
#include "HitRecord.h"
#include "AABB.h"

bool MovingSphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
    Vec3 oc = ray.Origin - Center(ray.Time);

    float a = ray.Direction.SqrMagnitude();
    float halfB = Vec3::Dot(ray.Direction, oc);
    float c = oc.SqrMagnitude() - Radius * Radius;

    float discriminant = halfB * halfB - a * c;

    if (discriminant < 0.0f) {
        return false;
    }

    float sqrtDiscriminant = std::sqrtf(discriminant);
    float t = (-halfB - sqrtDiscriminant) / a; // closer hit point

    if (t < tMin || tMax < t) {
        t = (-halfB + sqrtDiscriminant) / a; // farther hit point
        if (t < tMin || tMax < t) {
            return false;
        }
    }

    Vec3 point = ray.At(t);
    Vec3 outwardNormal = (point - Center(ray.Time)) / Radius;

    hitRecord.T = t;
    hitRecord.Point = point;
    hitRecord.SetFaceNormal(ray.Direction, outwardNormal);
    hitRecord.Material = Material;

    return true;
}

Vec3 MovingSphere::Center(float time) const {
    return Center0 + (Center1 - Center0) * ((time - Time0) / (Time1 - Time0));
}

bool MovingSphere::BoundingBox(float time0, float time1, AABB& aabbOut) const {
    Vec3 radiusVec = Vec3(Radius, Radius, Radius);

    AABB time0Box(
        Center(time0) - radiusVec,
        Center(time0) + radiusVec
    );
    AABB time1Box(
        Center(time1) - radiusVec,
        Center(time1) + radiusVec
    );

    aabbOut = AABB::SurroundingBox(time0Box, time1Box);

    return true;
}
