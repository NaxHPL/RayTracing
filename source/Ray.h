#pragma once

#include "Vec3.h"

struct Ray {
    Vec3 Origin;
    Vec3 Direction;

    Ray() { }

    Ray(const Vec3& origin, const Vec3& direction) : Origin(origin), Direction(direction) { }

    Vec3 At(float t) const {
        return Origin + t * Direction;
    }
};
