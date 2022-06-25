#pragma once

#include "Vec3.h"

struct Ray {
    Vec3 Origin;
    Vec3 Direction;
    float Time{ 0.0f };

    Ray() {}

    Ray(const Vec3& origin, const Vec3& direction, float time = 0.0f)
        : Origin(origin), Direction(direction), Time(time) { }

    Vec3 At(float t) const {
        return Origin + t * Direction;
    }
};
