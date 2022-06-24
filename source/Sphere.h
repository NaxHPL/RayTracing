#pragma once

#include <memory>
#include <cmath>
#include "Hittable.h"
#include "Vec3.h"
#include "RTWeekend.h"

struct Ray;
struct HitRecord;
struct Material;

struct Sphere : Hittable {
    Vec3 Center;
    float Radius{ 0.0f };
    std::shared_ptr<Material> Mat;

    Sphere() { }

    Sphere(const Vec3& center, float radius, std::shared_ptr<Material> material)
        : Center(center), Radius(radius), Mat(material) {}

    bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const override;

    bool BoundingBox(float time0, float time1, AABB& aabbOut) const override;

    static void GetUV(const Vec3& p, float& uOut, float& vOut) {
        // p: a given point on the sphere of radius one, centered at the origin.
        // u: returned value [0,1] of angle around the Y axis from X=-1.
        // v: returned value [0,1] of angle from Y=-1 to Y=+1.
        //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
        //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
        //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

        float theta = std::acosf(-p.Y);
        float phi = std::atan2f(-p.Z, p.X) + PI;

        uOut = phi / TWO_PI;
        vOut = theta / PI;
    }
};
