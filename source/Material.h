#pragma once

#include "Color.h"

struct Ray;
struct HitRecord;
struct Vec3;

struct Material {
    virtual bool Scatter(const Ray& rayIn, const HitRecord& hit, Ray& scatteredRay, Color& attenuation) const = 0;

    virtual Color Emitted(float u, float v, const Vec3& p) const { return Color::Black(); }
};
