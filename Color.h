#pragma once

#include <iostream>
#include "Vector3.h"

struct Color {
    float R;
    float G;
    float B;

    Color() : R(0.0f), G(0.0f), B(0.0f) { }

    Color(float r, float g, float b) : R(r), G(g), B(b) { }
};

void WriteColor(std::ostream& stream, Color color) {
    stream
        << static_cast<int>(255.999f * color.R) << ' '
        << static_cast<int>(255.999f * color.G) << ' '
        << static_cast<int>(255.999f * color.B) << '\n';
}
