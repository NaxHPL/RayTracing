#pragma once

#include "Vec3.h"

struct Ray {
    Point3 Origin;
    Vec3 Direction;

    Ray() { }

    Ray(const Point3& origin, const Vec3& direction) : Origin(origin), Direction(direction) { }

    Point3 At(float t) const {
        return Origin + t * Direction;
    }
};
