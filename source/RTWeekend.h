#pragma once

#include <limits>
#include <cstdlib>

const float INF_F = std::numeric_limits<float>::infinity();
const float PI = 3.1415926536f;
const float TWO_PI = PI * 2.0f;

enum struct Axis { X, Y, Z };

inline float DegreesToRadians(float degrees) {
    return degrees * PI / 180.0f;
}

inline float RadiansToDegrees(float radians) {
    return radians * 180.0f / PI;
}

inline float RandomFloat() {
    return std::rand() / (RAND_MAX + 1.0f);
}

inline float RandomFloat(float min, float max) {
    return min + (max - min) * RandomFloat();
}

inline int RandomInt() {
    return std::rand();
}

inline int RandomInt(int min, int max) {
    return min + (std::rand() % (max - min + 1));
}

inline float Clamp(float x, float min, float max) {
    return
        x < min ? min :
        x > max ? max :
        x;
}

inline int Clamp(int x, int min, int max) {
    return
        x < min ? min :
        x > max ? max :
        x;
}
