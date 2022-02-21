#include <cmath>
#include "Vec3.h"
#include "RTWeekend.h"

Vec3 Vec3::RandomInUnitSphere() {
    float u = RandomFloat();
    float v = RandomFloat();

    float theta = 2.0f * PI * u;
    float phi = std::acos(2.0f * v - 1.0f);

    float sinTheta = std::sin(theta);
    float cosTheta = std::cos(theta);
    float sinPhi = std::sin(phi);
    float cosPhi = std::cos(phi);

    float r = std::cbrtf(RandomFloat());
    float x = r * sinPhi * cosTheta;
    float y = r * sinPhi * sinTheta;
    float z = r * cosPhi;

    return Vec3(x, y, z);
}

Vec3 Vec3::RandomInUnitDisk() {
    float r = RandomFloat();
    float sqrtR = std::sqrtf(r);
    float theta = RandomFloat(0.0f, TWO_PI);

    return Vec3(
        sqrtR * std::cosf(theta),
        sqrtR * std::sinf(theta),
        0.0f
    );
}

Vec3 Vec3::RandomUnitVector() {
    Vec3 v = Vec3::RandomInUnitSphere();
    v.Normalize();
    return v;
}

Vec3 Vec3::RandomInHemisphere(const Vec3& normal) {
    Vec3 v = Vec3::RandomInUnitSphere();
    return Vec3::Dot(v, normal) > 0.0f ? v : -v;
}

Vec3 Vec3::Reflect(const Vec3& v, const Vec3& normal) {
    return v - 2.0f * Vec3::Dot(v, normal) * normal;
}

Vec3 Vec3::Refract(const Vec3& v, const Vec3& normal, float etaOverEtaPrime) {
    float cosTheta = std::fminf(Vec3::Dot(-v, normal), 1.0f);
    Vec3 perpendicular = etaOverEtaPrime * (v + cosTheta * normal);
    Vec3 parallel = -std::sqrtf(std::fabsf(1.0f - perpendicular.SqrMagnitude())) * normal;
    return perpendicular + parallel;
}
