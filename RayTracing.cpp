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
#include "IMaterial.h"
#include "Lambertian.h"
#include "Metal.h"

Color GetRayColor(const Ray& ray, const IHittable& world, int depth) {
    if (depth <= 0) {
        return Color::Black();;
    }

    HitRecord hit;
    if (world.Hit(ray, 0.001f, INF_F, hit)) {
        Ray scatteredRay;
        Color attenuation;

        if (hit.Material->Scatter(ray, hit, scatteredRay, attenuation)) {
            return attenuation * GetRayColor(scatteredRay, world, depth - 1);
        }

        return Color::Black();
    }

    Vec3 unitDirection = ray.Direction.Normalized();
    float t = 0.5f * (unitDirection.Y + 1.0f);
    return (1.0f - t) * Color::White() + t * Color(0.5f, 0.7f, 1.0f);
}

int main() {
    // Image

    const float aspectRatio = 16.0f / 9.0f;
    const int imageWidth = 400;
    const int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    // World

    std::shared_ptr<Lambertian> groundMaterial = std::make_shared<Lambertian>(Color(0.8f, 0.8f, 0.0f));
    std::shared_ptr<Lambertian> centerMaterial = std::make_shared<Lambertian>(Color(0.7f, 0.3f, 0.3f));
    std::shared_ptr<Metal> leftMaterial = std::make_shared<Metal>(Color(0.8f, 0.8f, 0.8f));
    std::shared_ptr<Metal> rightMaterial = std::make_shared<Metal>(Color(0.8f, 0.6f, 0.2f));

    HittableCollection world;

    world.Add(std::make_shared<Sphere>(Vec3(0.0f, -100.5f, -1.0f), 100.0f, groundMaterial));
    world.Add(std::make_shared<Sphere>(Vec3(0.0f, -0.0f, -1.0f), 0.5f, centerMaterial));
    world.Add(std::make_shared<Sphere>(Vec3(-1.0f, -0.0f, -1.0f), 0.5f, leftMaterial));
    world.Add(std::make_shared<Sphere>(Vec3(1.0f, -0.0f, -1.0f), 0.5f, rightMaterial));

    // Camera

    Camera camera;

    // Render

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
