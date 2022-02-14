#pragma once

#include <iostream>
#include "Vec3.h"

struct Color {
    float R;
    float G;
    float B;

    Color() : R(0.0f), G(0.0f), B(0.0f) { }

    Color(float r, float g, float b) : R(r), G(g), B(b) { }

    static Color White() {
        return Color(1.0f, 1.0f, 1.0f);
    }

    static Color Black() {
        return Color();
    }
};

Color operator+(const Color& rhs, const Color& lhs) {
    return Color(rhs.R + lhs.R, rhs.G + lhs.G, rhs.B + lhs.B);
}

Color operator-(const Color& rhs, const Color& lhs) {
    return Color(rhs.R - lhs.R, rhs.G - lhs.G, rhs.B - lhs.B);
}

Color operator*(const Color& v, const float t) {
    return Color(v.R * t, v.G * t, v.B * t);
}

Color operator*(const float t, const Color& v) {
    return Color(v.R * t, v.G * t, v.B * t);
}

void WriteColor(std::ostream& stream, Color color) {
    stream
        << static_cast<int>(255.999f * color.R) << ' '
        << static_cast<int>(255.999f * color.G) << ' '
        << static_cast<int>(255.999f * color.B) << '\n';
}
