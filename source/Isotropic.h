#pragma once

#include "Material.h"
#include "ITexture.h"
#include "SolidColor.h"
#include "Ray.h"
#include "HitRecord.h"
#include "Vec3.h"

struct Color;

struct Isotropic : Material {

	std::shared_ptr<ITexture> Albedo;

	Isotropic(Color color) : Albedo(std::make_shared<SolidColor>(color)) { }

	Isotropic(std::shared_ptr<ITexture> texture) : Albedo(texture) { }

	virtual bool Scatter(const Ray& rayIn, const HitRecord& hit, Ray& scatteredRay, Color& attenuation) const override {
		scatteredRay = Ray(hit.Point, Vec3::RandomInUnitSphere(), rayIn.Time);
		attenuation = Albedo->Value(hit.U, hit.V, hit.Point);
		return true;
	}
};