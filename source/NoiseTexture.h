#pragma once

#include <cmath>
#include "ITexture.h"
#include "Perlin.h"
#include "Color.h"

struct Vec3;

struct NoiseTexture : ITexture {
	Perlin Perlin;
	float Scale{ 1.0f };

	NoiseTexture() { }

	NoiseTexture(float scale) : Scale(scale) { }

	virtual Color Value(float u, float v, const Vec3& p) const override {
		float noise = 0.5f * (1.0f + std::sinf(Scale * p.Z + 10.0f * Perlin.Turbulence(p)));
		return Color::White() * noise;
	}
};