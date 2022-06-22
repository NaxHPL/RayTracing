#include <iostream>
#include <cmath>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "RTWeekend.h"
#include "Vec3.h"
#include "Ray.h"
#include "Color.h"
#include "Hittable.h"
#include "HitRecord.h"
#include "HittableCollection.h"
#include "Sphere.h"
#include "MovingSphere.h"
#include "Camera.h"
#include "IMaterial.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "BVHNode.h"
#include "CheckerTexture.h"

Color GetRayColor(const Ray& ray, const Hittable& world, int depth) {
    if (depth <= 0) {
        return Color::Black();
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

HittableCollection GetRandomScene() {
    HittableCollection world;

    std::shared_ptr<CheckerTexture> checker = std::make_shared<CheckerTexture>(Color(0.2f, 0.3f, 0.1f), Color(0.9f, 0.9f, 0.9f));
    world.Add(std::make_shared<Sphere>(Vec3(0.0f, -1000.0f, 0.0f), 1000.0f, std::make_shared<Lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            float chooseMat = RandomFloat();
            Vec3 center(a + 0.9f * RandomFloat(), 0.2f, b + 0.9f * RandomFloat());

            if ((center - Vec3(4.0f, 0.2f, 0.0f)).Magnitude() > 0.9f) {
                std::shared_ptr<IMaterial> sphereMat;

                if (chooseMat < 0.8f) {
                    // Diffuse
                    Color albedo = Color::Random() * Color::Random();
                    sphereMat = std::make_shared<Lambertian>(albedo);
                    Vec3 center2 = center + Vec3(0.0f, RandomFloat(0.0f, 0.5f), 0.0f);
                    world.Add(std::make_shared<MovingSphere>(center, center2, 0.0f, 1.0f, 0.2f, sphereMat));
                }
                else if (chooseMat > 0.95f) {
                    // Metal
                    Color albedo = Color::Random(0.5f, 1.0f);
                    float fuzziness = RandomFloat(0.0f, 0.5f);
                    sphereMat = std::make_shared<Metal>(albedo, fuzziness);
                    world.Add(std::make_shared<Sphere>(center, 0.2f, sphereMat));
                }
                else {
                    // Glass
                    sphereMat = std::make_shared<Dielectric>(1.5f);
                    world.Add(std::make_shared<Sphere>(center, 0.2f, sphereMat));
                }
            }
        }
    }

    std::shared_ptr<Dielectric> mat1 = std::make_shared<Dielectric>(1.5f);
    world.Add(std::make_shared<Sphere>(Vec3(0.0f, 1.0f, 0.0f), 1.0f, mat1));

    std::shared_ptr<Lambertian> mat2 = std::make_shared<Lambertian>(Color(0.4f, 0.2f, 0.1f));
    world.Add(std::make_shared<Sphere>(Vec3(-4.0f, 1.0f, 0.0f), 1.0f, mat2));

    std::shared_ptr<Metal> mat3 = std::make_shared<Metal>(Color(0.7f, 0.6f, 0.5f), 0.0f);
    world.Add(std::make_shared<Sphere>(Vec3(4.0f, 1.0f, 0.0f), 1.0f, mat3));

    HittableCollection world2;
    world2.Add(std::make_shared<BVHNode>(world, 0.0f, 1.0f));

    return world2;
}

int main() {

    std::srand((unsigned)std::time(NULL));

    // Image

    const float aspectRatio = 16.9f / 9.0f;
    const int imageWidth = 200;
    const int samplesPerPixel = 50;
    const int maxDepth = 25;

    // World

    HittableCollection world = GetRandomScene();

    // Camera

    Vec3 lookFrom(13.0f, 2.0f, 3.0f);
    Vec3 lookAt = Vec3::Zero();
    Vec3 vUp = Vec3::Up();
    float verticalFov = 20.0f;
    float aperture = 0.1f;
    float focusDistance = 10.0f;
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    Camera camera(lookFrom, lookAt, vUp, verticalFov, aspectRatio, aperture, focusDistance, 0.0f, 1.0f);

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
