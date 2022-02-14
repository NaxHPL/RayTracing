#pragma once

struct Vector3 {
    float X;
    float Y;
    float Z;

    Vector3() : X(0.0f), Y(0.0f), Z(0.0f) { }

    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) { }

    Vector3& operator+=(const Vector3& v) {
        X += v.X;
        Y += v.Y;
        Z += v.Z;
        return *this;
    }

    Vector3& operator-=(const Vector3& v) {
        X -= v.X;
        Y -= v.Y;
        Z -= v.Z;
        return *this;
    }

    Vector3& operator*=(const float t) {
        X *= t;
        Y *= t;
        Z *= t;
        return *this;
    }

    Vector3& operator/=(const float t) {
        X /= t;
        Y /= t;
        Z /= t;
        return *this;
    }

    float Magnitude() const {
        return std::sqrtf(X * X + Y * Y + Z * Z);
    }

    float MagnitudeSquared() const {
        return X * X + Y * Y + Z * Z;
    }

    Vector3 Normalized() {
        float m = Magnitude();
        return Vector3(X / m, Y / m, Z / m);
    }

    void Normalize() {
        float m = this->Magnitude();
        if (m > 0.0f) {
            X /= m;
            Y /= m;
            Z /= m;
        }
    }

    static float Dot(const Vector3& v1, const Vector3& v2) {
        return
            v1.X * v2.X +
            v1.Y * v2.Y +
            v1.Z * v2.Z;
    }

    static Vector3 Cross(const Vector3& v1, const Vector3& v2) {
        return Vector3(
            v1.Y * v2.Z - v1.Z * v2.Y,
            v1.Z * v2.X - v1.X * v2.Z,
            v1.X * v2.Y - v1.Y * v2.X
        );
    }

    static Vector3 Zero() {
        return Vector3();
    }

    static Vector3 One() {
        return Vector3(1.0f, 1.0f, 1.0f);
    }
};

using Point3 = Vector3;

Vector3 operator-(const Vector3& v) {
    return Vector3(-v.X, -v.Y, -v.Z);
}

Vector3 operator+(const Vector3& rhs, const Vector3& lhs) {
    return Vector3(rhs.X + lhs.X, rhs.Y + lhs.Y, rhs.Z + lhs.Z);
}

Vector3 operator-(const Vector3& rhs, const Vector3& lhs) {
    return Vector3(rhs.X - lhs.X, rhs.Y - lhs.Y, rhs.Z - lhs.Z);
}

Vector3 operator*(const Vector3& v, const float t) {
    return Vector3(v.X * t, v.Y * t, v.Z * t);
}

Vector3 operator*(const float t, const Vector3& v) {
    return Vector3(v.X * t, v.Y * t, v.Z * t);
}

Vector3 operator*(const Vector3& rhs, const Vector3& lhs) {
    return Vector3(rhs.X * lhs.X, rhs.Y * lhs.Y, rhs.Z * lhs.Z);
}

Vector3 operator/(const Vector3& v, const float t) {
    return Vector3(v.X / t, v.Y / t, v.Z / t);
}

std::ostream& operator<<(std::ostream& stream, const Vector3& v) {
    return stream << '[' << v.X << ", " << v.Y << ", " << v.Z << ']';
}
