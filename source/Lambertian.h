#pragma once

#include <memory>
#include "IMaterial.h"
#include "Color.h"
#include "Vec3.h"
#include "HitRecord.h"
#include "Ray.h"
#include "ITexture.h"
#include "SolidColor.h"

struct Lambertian : IMaterial {
    std::shared_ptr<ITexture> Albedo;

    Lambertian(const Color& albedo) : Albedo(std::make_shared<SolidColor>(albedo)) { }

    Lambertian(std::shared_ptr<ITexture> texture) : Albedo(texture) { }

    bool Scatter(const Ray& rayIn, const HitRecord& hit, Ray& scatteredRay, Color& attenuation) const override {
        Vec3 scatterDirection = hit.Normal + Vec3::RandomUnitVector();

        if (scatterDirection.IsNearZero()) {
            scatterDirection = hit.Normal;
        }

        scatteredRay = Ray(hit.Point, scatterDirection, rayIn.Time);
        attenuation = Albedo->Value(hit.U, hit.V, hit.Point);
        return true;
    }
};
