#pragma once

#include "Vec3.h"

struct HitRecord {
    float T;
    Vec3 Point;
    Vec3 Normal;
    bool FrontFace;

    void SetFaceNormal(const Vec3& rayDirection, const Vec3& outwardNormal) {
        FrontFace = Vec3::Dot(rayDirection, outwardNormal) < 0.0f;
        Normal = FrontFace ? outwardNormal : -outwardNormal;
    }
};
