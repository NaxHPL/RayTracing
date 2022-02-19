#include <iostream>
#include <cmath>
#include <memory>
#include "RTWeekend.h"
#include "Vec3.h"
#include "Ray.h"
#include "Color.h"
#include "IHittable.h"
#include "HitRecord.h"
#include "HittableCollection.h"
#include "Sphere.h"
#include "Camera.h"

Color GetRayColor(const Ray& ray, const IHittable& world, int depth) {
    if (depth <= 0) {
        return Color::Black();;
    }

    HitRecord hit;
    if (world.Hit(ray, 0.001f, INF_F, hit)) {
        Vec3 target = hit.Point + hit.Normal + Vec3::RandomInUnitSphere();
        return 0.5f * GetRayColor(Ray(hit.Point, target - hit.Point), world, depth - 1);
    }

    Vec3 unitDirection = ray.Direction.Normalized();
    float t = 0.5f * (unitDirection.Y + 1.0f);
    return (1.0f - t) * Color::White() + t * Color(0.5f, 0.7f, 1.0f);
}

int main() {
    const float aspectRatio = 16.0f / 9.0f;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    HittableCollection world;
    world.Add(std::make_shared<Sphere>(Vec3(0.0f, 0.0f, -1.0f), 0.5f));
    world.Add(std::make_shared<Sphere>(Vec3(0.0f, -100.5f, -1.0f), 100.0f));

    Camera camera;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << '\n' << "255\n";

    for (int i = imageHeight - 1; i >= 0; i--) {
        std::cerr << "\nScanlines remaining: " << i << ' ' << std::flush;
        for (int j = 0; j < imageWidth; j++) {
            Color pixelColor = Color::Black();
            for (int s = 0; s < samplesPerPixel; s++) {
                float u = (j + RandomFloat()) / (imageWidth - 1);
                float v = (i + RandomFloat()) / (imageHeight - 1);
                Ray ray = camera.GetRay(u, v);
                pixelColor += GetRayColor(ray, world, maxDepth);
            }
            pixelColor.WritePPM(std::cout, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}
