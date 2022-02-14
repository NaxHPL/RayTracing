#include <iostream>
#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

Color GetRayColor(const Ray& ray) {
    Vec3 dir = ray.Direction.Normalized();
    float t = 0.5f * (dir.Y + 1.0f);
    return (1.0f - t) * Color::White() + t * Color(0.5f, 0.7f, 1.0f);
}

int main() {
    const float aspectRatio = 16.0f / 9.0f;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    float viewportHeight = 2.0f;
    float viewportWidth = viewportHeight * aspectRatio;
    float focalLength = 1.0f;

    Point3 origin(0.0f, 0.0f, 0.0f);
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

            WriteColor(std::cout, rayColor);
        }
    }

    std::cerr << "\nDone\n";
}
