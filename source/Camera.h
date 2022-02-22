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
    float t0, t1;

public:
    Camera(Vec3 lookFrom,
           Vec3 lookAt,
           Vec3 vUp,
           float verticalFov,
           float aspectRatio,
           float aperture,
           float focusDistance,
           float time0 = 0.0f,
           float time1 = 0.0f);

    Ray GetRay(float s, float t) const;
};
