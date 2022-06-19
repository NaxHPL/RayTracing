#pragma once

#include <memory>
#include "Vec3.h"

struct IMaterial;

struct HitRecord {
    float T{ 0.0f };
    float U;
    float V;
    Vec3 Point;
    Vec3 Normal;
    bool FrontFace{ false };
    std::shared_ptr<IMaterial> Material;

    void SetFaceNormal(const Vec3& rayDirection, const Vec3& outwardNormal) {
        FrontFace = Vec3::Dot(rayDirection, outwardNormal) < 0.0f;
        Normal = FrontFace ? outwardNormal : -outwardNormal;
    }
};
