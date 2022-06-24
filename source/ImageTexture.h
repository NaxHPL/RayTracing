#pragma once

#include <iostream>
#include "ITexture.h"
#include "RTWeekendStbImage.h"
#include "RTWeekend.h"
#include "Color.h"

struct Vec3;

struct ImageTexture : ITexture {
	
private:
	unsigned char* data{ nullptr };
	int width{ 0 };
	int height{ 0 };
	int bytesPerScanline{ 0 };

public:
	static const int bytesPerPixel = 3;

	ImageTexture() { }

	ImageTexture(const char* fileName) {
		int componentsPerPixel = bytesPerPixel;
		data = stbi_load(fileName, &width, &height, &componentsPerPixel, componentsPerPixel);

		if (!data) {
			std::cerr << "ERROR: Could not load texture image file '" << fileName << "'.\n";
			width = height = 0;
		}

		bytesPerScanline = bytesPerPixel * width;
	}

	~ImageTexture() {
		delete data;
	}

	virtual Color Value(float u, float v, const Vec3& p) const override {
		if (data == nullptr) {
			return Color(1.0f, 0.0f, 1.0f);
		}

		u = Clamp(u, 0.0f, 1.0f);
		v = 1.0f - Clamp(v, 0.0f, 1.0f);

		int i = static_cast<int>(width * u);
		int j = static_cast<int>(height * v);

		i = Clamp(i, 0, width - 1);
		j = Clamp(j, 0, height - 1);

		unsigned char* pixel = data + j * bytesPerScanline + i * bytesPerPixel;
		const float colorScale = 1.0f / 255.0f;

		float r = pixel[0] * colorScale;
		float g = pixel[1] * colorScale;
		float b = pixel[2] * colorScale;

		return Color(r, g, b);
	}
};