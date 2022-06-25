#pragma once

#include <iostream>
#include <cmath>
#include "RTWeekend.h"

struct Vec3 {
    float X;
    float Y;
    float Z;

    Vec3() : X(0.0f), Y(0.0f), Z(0.0f) { }

    Vec3(float x, float y, float z) : X(x), Y(y), Z(z) { }

    Vec3& operator+=(const Vec3& v) {
        X += v.X;
        Y += v.Y;
        Z += v.Z;
        return *this;
    }

    Vec3& operator-=(const Vec3& v) {
        X -= v.X;
        Y -= v.Y;
        Z -= v.Z;
        return *this;
    }

    Vec3& operator*=(const float t) {
        X *= t;
        Y *= t;
        Z *= t;
        return *this;
    }

    Vec3& operator/=(const float t) {
        X /= t;
        Y /= t;
        Z /= t;
        return *this;
    }

    // Get by Axis
    float operator[](const Axis axis) const {
        switch (axis) {
            case Axis::X: return X;
            case Axis::Y: return Y;
            default:      return Z;
        }
    }

    // Set by Axis
    float& operator[](const Axis axis) {
        switch (axis) {
            case Axis::X: return X;
            case Axis::Y: return Y;
            default:      return Z;
        }
    }

    float Magnitude() const {
        return std::sqrtf(X * X + Y * Y + Z * Z);
    }

    float SqrMagnitude() const {
        return X * X + Y * Y + Z * Z;
    }

    Vec3 Normalized() const {
        float m = Magnitude();
        return Vec3(X / m, Y / m, Z / m);
    }

    void Normalize() {
        float m = Magnitude();
        if (m > 0.0f) {
            X /= m;
            Y /= m;
            Z /= m;
        }
    }

    bool IsNearZero() const {
        const float epsilon = 1e-6f;
        return
            std::fabs(X) < epsilon &&
            std::fabs(Y) < epsilon &&
            std::fabs(Z) < epsilon;
    }

    static float Dot(const Vec3& v1, const Vec3& v2) {
        return
            v1.X * v2.X +
            v1.Y * v2.Y +
            v1.Z * v2.Z;
    }

    static Vec3 Cross(const Vec3& v1, const Vec3& v2) {
        return Vec3(
            v1.Y * v2.Z - v1.Z * v2.Y,
            v1.Z * v2.X - v1.X * v2.Z,
            v1.X * v2.Y - v1.Y * v2.X
        );
    }

    static Vec3 Zero() {
        return Vec3();
    }

    static Vec3 One() {
        return Vec3(1.0f, 1.0f, 1.0f);
    }

    static Vec3 Right() {
        return Vec3(1.0f, 0.0f, 0.0f);
    }

    static Vec3 Up() {
        return Vec3(0.0f, 1.0f, 0.0f);
    }

    static Vec3 Forward() {
        return Vec3(0.0f, 0.0f, -1.0f);
    }

    static Vec3 Random() {
        return Vec3(RandomFloat(), RandomFloat(), RandomFloat());
    }

    static Vec3 Random(float min, float max) {
        return Vec3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
    }

    static Vec3 RandomInUnitSphere();

    static Vec3 RandomInUnitDisk();

    static Vec3 RandomUnitVector();

    static Vec3 RandomInHemisphere(const Vec3& normal);

    static Vec3 Reflect(const Vec3& v, const Vec3& normal);

    static Vec3 Refract(const Vec3& v, const Vec3& normal, float etaOverEtaPrime);
};

inline Vec3 operator-(const Vec3& v) {
    return Vec3(-v.X, -v.Y, -v.Z);
}

inline Vec3 operator+(const Vec3& rhs, const Vec3& lhs) {
    return Vec3(rhs.X + lhs.X, rhs.Y + lhs.Y, rhs.Z + lhs.Z);
}

inline Vec3 operator-(const Vec3& rhs, const Vec3& lhs) {
    return Vec3(rhs.X - lhs.X, rhs.Y - lhs.Y, rhs.Z - lhs.Z);
}

inline Vec3 operator*(const Vec3& v, const float t) {
    return Vec3(v.X * t, v.Y * t, v.Z * t);
}

inline Vec3 operator*(const float t, const Vec3& v) {
    return v * t;
}

inline Vec3 operator/(const Vec3& v, const float t) {
    return Vec3(v.X / t, v.Y / t, v.Z / t);
}

inline bool operator==(const Vec3& rhs, const Vec3& lhs) {
    return
        rhs.X == lhs.X &&
        rhs.Y == lhs.Y &&
        rhs.Z == lhs.Z;
}

inline std::ostream& operator<<(std::ostream& stream, const Vec3& v) {
    return stream << '[' << v.X << ", " << v.Y << ", " << v.Z << ']';
}
