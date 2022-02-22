#pragma once

#include <cmath>
#include "RTWeekend.h"
#include "IMaterial.h"
#include "Color.h"
#include "Vec3.h"
#include "Ray.h"
#include "HitRecord.h"

struct Dielectric : IMaterial {
    float IndexOfRefraction;

    Dielectric(float indexOfRefraction) : IndexOfRefraction(indexOfRefraction) { }

    bool Scatter(const Ray& rayIn, const HitRecord& hit, Ray& scatteredRay, Color& attenuation) const override {
        float refRatio = hit.FrontFace ? 1.0f / IndexOfRefraction : IndexOfRefraction;
        Vec3 normalizedDir = rayIn.Direction.Normalized();

        float cosTheta = std::fminf(Vec3::Dot(-normalizedDir, hit.Normal), 1.0f);
        float sinTheta = std::sqrtf(1.0f - cosTheta * cosTheta);
        bool cannotRefract = refRatio * sinTheta > 1.0f;

        Vec3 rDirection = cannotRefract || Reflectance(cosTheta, refRatio) > RandomFloat() ?
            Vec3::Reflect(normalizedDir, hit.Normal) :
            Vec3::Refract(normalizedDir, hit.Normal, refRatio);

        scatteredRay = Ray(hit.Point, rDirection, rayIn.Time);
        attenuation = Color::White();

        return true;
    }

private:
    static float Reflectance(float cosine, float refIndex) {
        // Schlick's approximation
        float r0 = (1.0f - refIndex) / (1.0f + refIndex);
        r0 *= r0;
        return r0 + (1.0f - r0) * std::powf((1.0f - cosine), 5.0f);
    }
};
