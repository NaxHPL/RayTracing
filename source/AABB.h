#pragma once

#include <cmath>
#include "Vec3.h"

struct Ray;

struct AABB {
    Vec3 Minimum;
    Vec3 Maximum;

    AABB() { }

    AABB(const Vec3& minimum, const Vec3& maximum) : Minimum(minimum), Maximum(maximum) { }

    bool Hit(const Ray& ray, float tMin, float tMax) const;

    static AABB SurroundingBox(const AABB& aabb1, const AABB& aabb2) {
        AABB aabbRet;
        SurroundingBox(aabb1, aabb2, aabbRet);
        return aabbRet;
    }

    static void SurroundingBox(const AABB& aabb1, const AABB& aabb2, AABB& aabbOut) {
        Vec3 min(
            std::fminf(aabb1.Minimum.X, aabb2.Minimum.X),
            std::fminf(aabb1.Minimum.Y, aabb2.Minimum.Y),
            std::fminf(aabb1.Minimum.Z, aabb2.Minimum.Z)
        );
        Vec3 max(
            std::fmaxf(aabb1.Maximum.X, aabb2.Maximum.X),
            std::fmaxf(aabb1.Maximum.Y, aabb2.Maximum.Y),
            std::fmaxf(aabb1.Maximum.Z, aabb2.Maximum.Z)
        );

        aabbOut.Minimum = min;
        aabbOut.Maximum = max;
    }
};
