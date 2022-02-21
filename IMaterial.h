#pragma once

struct Ray;
struct HitRecord;
struct Color;

struct IMaterial {
    virtual bool Scatter(const Ray& rayIn, const HitRecord& hit, Ray& scatteredRay, Color& attenuation) const = 0;
};
