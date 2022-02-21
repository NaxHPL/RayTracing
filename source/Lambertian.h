#pragma once

#include "IMaterial.h"
#include "Color.h"
#include "Vec3.h"
#include "HitRecord.h"
#include "Ray.h"

struct Lambertian : IMaterial {
    Color Albedo;

    Lambertian(const Color& albedo) : Albedo(albedo) { }

    bool Scatter(const Ray& rayIn, const HitRecord& hit, Ray& scatteredRay, Color& attenuation) const override {
        Vec3 scatterDirection = hit.Normal + Vec3::RandomUnitVector();

        if (scatterDirection.IsNearZero()) {
            scatterDirection = hit.Normal;
        }

        scatteredRay = Ray(hit.Point, scatterDirection);
        attenuation = Albedo;
        return true;
    }
};
