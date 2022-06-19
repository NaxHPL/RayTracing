#include <cmath>
#include "Sphere.h"
#include "Vec3.h"
#include "Ray.h"
#include "HitRecord.h"
#include "AABB.h"

bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
    Vec3 oc = ray.Origin - Center;

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
    Vec3 outwardNormal = (point - Center) / Radius;

    hitRecord.T = t;
    hitRecord.Point = point;
    hitRecord.SetFaceNormal(ray.Direction, outwardNormal);
    GetUV(point, hitRecord.U, hitRecord.V);
    hitRecord.Material = Material;

    return true;
}

bool Sphere::BoundingBox(float time0, float time1, AABB& aabbOut) const {
    Vec3 radiusVec = Vec3(Radius, Radius, Radius);
    aabbOut.Minimum = Center - radiusVec;
    aabbOut.Maximum = Center + radiusVec;
    return true;
}
