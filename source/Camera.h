#pragma once

#include "Vec3.h"

struct Ray;

class Camera {
    Vec3 origin;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 lowerLeftCorner;
    Vec3 u, v, w;
    float lensRadius;

public:
    Camera(Vec3 lookFrom,
           Vec3 lookAt,
           Vec3 vUp,
           float verticalFov,
           float aspectRatio,
           float aperture,
           float focusDistance);

    Ray GetRay(float s, float t) const;
};
