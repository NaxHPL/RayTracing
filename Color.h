#pragma once

#include <iostream>
#include <cmath>
#include "RTWeekend.h"

struct Color {
    float R;
    float G;
    float B;

    Color() : R(0.0f), G(0.0f), B(0.0f) { }

    Color(float r, float g, float b) : R(r), G(g), B(b) { }

    Color& operator+=(const Color& c) {
        R += c.R;
        G += c.G;
        B += c.B;
        return *this;
    }

    Color& operator-=(const Color& c) {
        R -= c.R;
        G -= c.G;
        B -= c.B;
        return *this;
    }

    Color& operator*=(const float t) {
        R *= t;
        G *= t;
        B *= t;
        return *this;
    }

    Color& operator/=(const float t) {
        R /= t;
        G /= t;
        B /= t;
        return *this;
    }

    void WritePPM(std::ostream& stream, int samplesPerPixel) const {
        float scale = 1.0f / samplesPerPixel;
        float r = std::sqrtf(R * scale);
        float g = std::sqrtf(G * scale);
        float b = std::sqrtf(B * scale);

        stream
            << static_cast<int>(256.0f * Clamp(r, 0.0f, 0.999f)) << ' '
            << static_cast<int>(256.0f * Clamp(g, 0.0f, 0.999f)) << ' '
            << static_cast<int>(256.0f * Clamp(b, 0.0f, 0.999f)) << '\n';
    }

    static Color Black() {
        return Color();
    }

    static Color White() {
        return Color(1.0f, 1.0f, 1.0f);
    }

    static Color Grey() {
        return Color(0.5f, 0.5f, 0.5f);
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

    static Color Random() {
        return Color(RandomFloat(), RandomFloat(), RandomFloat());
    }

    static Color Random(float min, float max) {
        return Color(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
    }
};

inline Color operator+(const Color& rhs, const Color& lhs) {
    return Color(rhs.R + lhs.R, rhs.G + lhs.G, rhs.B + lhs.B);
}

inline Color operator-(const Color& rhs, const Color& lhs) {
    return Color(rhs.R - lhs.R, rhs.G - lhs.G, rhs.B - lhs.B);
}

inline Color operator*(const Color& c, const float t) {
    return Color(c.R * t, c.G * t, c.B * t);
}

inline Color operator*(const float t, const Color& c) {
    return Color(c.R * t, c.G * t, c.B * t);
}

inline Color operator*(const Color& c1, const Color& c2) {
    return Color(c1.R * c2.R, c1.G * c2.G, c1.B * c2.B);
}
