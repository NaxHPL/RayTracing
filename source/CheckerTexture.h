#pragma once

#include <memory>
#include <cmath>
#include "ITexture.h"
#include "SolidColor.h"

struct CheckerTexture : ITexture {
	std::shared_ptr<ITexture> Texture1;
	std::shared_ptr<ITexture> Texture2;

	CheckerTexture() { }

	CheckerTexture(std::shared_ptr<ITexture> texture1, std::shared_ptr<ITexture> texture2)
		: Texture1(texture1), Texture2(texture2) { }

	CheckerTexture(const Color& color1, const Color& color2)
		: Texture1(std::make_shared<SolidColor>(color1)), Texture2(std::make_shared<SolidColor>(color2)) { }

	virtual Color Value(float u, float v, const Vec3& p) const override {
		float sinX = std::sinf(10.0f * p.X);
		float sinY = std::sinf(10.0f * p.Y);
		float sinZ = std::sinf(10.0f * p.Z);

		return sinX * sinY * sinZ > 0.0f ?
			Texture1->Value(u, v, p) :
			Texture2->Value(u, v, p);
	}
};