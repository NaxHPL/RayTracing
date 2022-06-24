#pragma once

#include "Material.h"
#include "SolidColor.h"

struct ITexture;
struct Color;
struct Ray;
struct HitRecord;

struct DiffuseLight : Material {
	std::shared_ptr<ITexture> Texture;

	DiffuseLight(std::shared_ptr<ITexture> texture) : Texture(texture) { }

	DiffuseLight(Color color) : Texture(std::make_shared<SolidColor>(color)) { }

	virtual bool Scatter(const Ray& rayIn, const HitRecord& hit, Ray& scatteredRay, Color& attenuation) const override {
		return false;
	}

	virtual Color Emitted(float u, float v, const Vec3& p) const override {
		return Texture->Value(u, v, p);
	}
};