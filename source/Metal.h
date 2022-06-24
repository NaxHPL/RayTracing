#pragma once

#include "Material.h"
#include "Color.h"
#include "Vec3.h"
#include "Ray.h"
#include "HitRecord.h"

struct Metal : Material {
    Color Albedo;
    float Fuzziness;

    Metal(const Color& albedo, float fuzziness)
        : Albedo(albedo), Fuzziness(fuzziness < 1.0f ? fuzziness : 1.0f) { }

    bool Scatter(const Ray& rayIn, const HitRecord& hit, Ray& scatteredRay, Color& attenuation) const override {
        Vec3 reflected = Vec3::Reflect(rayIn.Direction.Normalized(), hit.Normal);
        scatteredRay = Ray(hit.Point, reflected + Fuzziness * Vec3::RandomInUnitSphere(), rayIn.Time);
        attenuation = Albedo;

        return Vec3::Dot(reflected, hit.Normal) > 0.0f;
    }
};
