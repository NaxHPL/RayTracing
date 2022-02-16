#include <iostream>
#include <cmath>
#include "Vec3.h"
#include "Ray.h"
#include "Color.h"

float RayHitSphere(const Ray& ray, const Vec3& sphereCenter, float sphereRadius) {
    Vec3 oc = ray.Origin - sphereCenter;

    float a = ray.Direction.SqrMagnitude();
    float halfB = Vec3::Dot(ray.Direction, oc);
    float c = oc.SqrMagnitude() - sphereRadius * sphereRadius;
    float discriminant = halfB * halfB - a * c;

    if (discriminant < 0.0f) {
        return -1.0f;
    }
    else {
        return (-halfB - std::sqrtf(discriminant)) / a;
    }
}

Color GetRayColor(const Ray& ray) {
    float t = RayHitSphere(ray, Vec3(0.0f, 0.0f, -1.0f), 0.5f);
    if (t > 0.0f) {
        Vec3 normal = (ray.At(t) - Vec3(0.0f, 0.0f, -1.0f)).Normalized();
        return 0.5f * Color(normal.X + 1.0f, normal.Y + 1.0f, normal.Z + 1.0f);
    }

    Vec3 dir = ray.Direction.Normalized();
    t = 0.5f * (dir.Y + 1.0f);
    return (1.0f - t) * Color::White() + t * Color(0.5f, 0.7f, 1.0f);
}

int main() {
    const float aspectRatio = 16.0f / 9.0f;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    float viewportHeight = 2.0f;
    float viewportWidth = viewportHeight * aspectRatio;
    float focalLength = 1.0f;

    Vec3 origin(0.0f, 0.0f, 0.0f);
    Vec3 horizontal(viewportWidth, 0.0f, 0.0f);
    Vec3 vertical(0.0f, viewportHeight, 0.0f);
    Vec3 lowerLeftCorner = origin - horizontal / 2.0f - vertical / 2.0f - Vec3(0.0f, 0.0f, focalLength);

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << '\n' << "255\n";

    for (int i = imageHeight - 1; i >= 0; i--) {
        std::cerr << "\nScanlines remaining: " << i << ' ' << std::flush;
        for (int j = 0; j < imageWidth; j++) {
            float u = static_cast<float>(j) / (imageWidth - 1);
            float v = static_cast<float>(i) / (imageHeight - 1);

            Ray ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
            Color rayColor = GetRayColor(ray);

            rayColor.WritePPM(std::cout);
        }
    }

    std::cerr << "\nDone\n";
}
