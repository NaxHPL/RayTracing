#pragma once

#include "ITexture.h"
#include "Color.h"

struct SolidColor : ITexture {

private:
    Color colorValue;

public:
    SolidColor() {}

    SolidColor(Color color) : colorValue(color) {}

    SolidColor(float r, float g, float b) : colorValue(Color(r, g, b)) {}

    virtual Color Value(float u, float v, const Vec3& p) const override {
        return colorValue;
    }
};