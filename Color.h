#pragma once

#include <iostream>

struct Color {
    float R;
    float G;
    float B;

    Color() : R(0.0f), G(0.0f), B(0.0f) { }

    Color(float r, float g, float b) : R(r), G(g), B(b) { }

    void WritePPM(std::ostream& stream) const {
        stream
            << static_cast<int>(255.999f * R) << ' '
            << static_cast<int>(255.999f * G) << ' '
            << static_cast<int>(255.999f * B) << '\n';
    }

    static Color Black() {
        return Color();
    }

    static Color White() {
        return Color(1.0f, 1.0f, 1.0f);
    }

    static Color Red() {
        return Color(1.0f, 0.0f, 0.0f);
    }

    static Color Green() {
        return Color(0.0f, 1.0f, 0.0f);
    }

    static Color Blue() {
        return Color(0.0f, 0.0f, 1.0f);
    }
};

inline Color operator+(const Color& rhs, const Color& lhs) {
    return Color(rhs.R + lhs.R, rhs.G + lhs.G, rhs.B + lhs.B);
}

inline Color operator-(const Color& rhs, const Color& lhs) {
    return Color(rhs.R - lhs.R, rhs.G - lhs.G, rhs.B - lhs.B);
}

inline Color operator*(const Color& v, const float t) {
    return Color(v.R * t, v.G * t, v.B * t);
}

inline Color operator*(const float t, const Color& v) {
    return Color(v.R * t, v.G * t, v.B * t);
}
