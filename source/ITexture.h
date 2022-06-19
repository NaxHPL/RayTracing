#pragma once

struct Color;
struct Vec3;

struct ITexture {
    virtual Color Value(float u, float v, const Vec3& p) const = 0;
};