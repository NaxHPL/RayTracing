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
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include "BVHNode.h"
#include "CheckerTexture.h"
#include "NoiseTexture.h"
#include "ImageTexture.h"
#include "DiffuseLight.h"
#include "AARectangle.h"
#include "Box.h"
#include "Translate.h"
#include "Rotate.h"

Color GetRayColor(const Ray& ray, const Color& backgroundColor, const Hittable& world, int depth) {
    if (depth <= 0) {
        return Color::Black();
    }

    HitRecord hit;
    if (!world.Hit(ray, 0.001f, INF_F, hit)) {
        return backgroundColor;
    }

    Ray scattered;
    Color attenuation;
    Color emitted = hit.Material->Emitted(hit.U, hit.V, hit.Point);

    if (!hit.Material->Scatter(ray, hit, scattered, attenuation)) {
        return emitted;
    }

    return emitted + attenuation * GetRayColor(scattered, backgroundColor, world, depth - 1);
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
                std::shared_ptr<Material> sphereMat;

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

    return HittableCollection(std::make_shared<BVHNode>(world, 0.0f, 1.0f));
}

HittableCollection GetTwoSpheresScene() {
    HittableCollection objects;
    std::shared_ptr<CheckerTexture> checkerTexture = std::make_shared<CheckerTexture>(Color(0.2f, 0.3f, 0.1f), Color(0.9f, 0.9f, 0.9f));

    objects.Add(std::make_shared<Sphere>(Vec3(0.0f, -10.0f, 0.0f), 10.0f, std::make_shared<Lambertian>(checkerTexture)));
    objects.Add(std::make_shared<Sphere>(Vec3(0.0f, 10.0f, 0.0f), 10.0f, std::make_shared<Lambertian>(checkerTexture)));

    return HittableCollection(std::make_shared<BVHNode>(objects, 0.0f, 1.0f));
}

HittableCollection GetTwoPerlinSpheresScene() {
    HittableCollection objects;
    std::shared_ptr<NoiseTexture> noiseTexture = std::make_shared<NoiseTexture>(4.0f);

    objects.Add(std::make_shared<Sphere>(Vec3(0.0f, -1000.0f, 0.0f), 1000.0f, std::make_shared<Lambertian>(noiseTexture)));
    objects.Add(std::make_shared<Sphere>(Vec3(0.0f, 2.0f, 0.0f), 2.0f, std::make_shared<Lambertian>(noiseTexture)));

    return HittableCollection(std::make_shared<BVHNode>(objects, 0.0f, 1.0f));
}

HittableCollection GetEarthScene() {
    std::shared_ptr<ImageTexture> earthTexture = std::make_shared<ImageTexture>("earthmap.jpg");
    std::shared_ptr<Lambertian> earthMaterial = std::make_shared<Lambertian>(earthTexture);

    std::shared_ptr<Hittable> globe = std::make_shared<Sphere>(Vec3::Zero(), 2.0f, earthMaterial);
    globe = std::make_shared<RotateZ>(globe, 90.0f);

    return HittableCollection(globe);
}

HittableCollection GetSimpleLightScene() {
    HittableCollection objects;

    std::shared_ptr<NoiseTexture> perlinTexture = std::make_shared<NoiseTexture>(4.0f);
    objects.Add(std::make_shared<Sphere>(Vec3(0.0f, -1000.0f, 0.0f), 1000.0f, std::make_shared<Lambertian>(perlinTexture)));
    objects.Add(std::make_shared<Sphere>(Vec3(0.0f, 2.0f, 0.0f), 2.0f, std::make_shared<Lambertian>(perlinTexture)));

    std::shared_ptr<DiffuseLight> whiteLight = std::make_shared<DiffuseLight>(Color(2.5f, 2.5f, 2.5f));
    objects.Add(std::make_shared<Sphere>(Vec3(0.0f, 7.0f, 0.0f), 2.0f, whiteLight));

    std::shared_ptr<DiffuseLight> blueLight = std::make_shared<DiffuseLight>(Color(0.5f, 0.5f, 4.0f));
    objects.Add(std::make_shared<XYRectangle>(3.0f, 5.0f, 1.0f, 3.0f, -2.0f, blueLight));

    return HittableCollection(std::make_shared<BVHNode>(objects, 0.0f, 1.0f));
}

HittableCollection GetCornellBoxScene() {
    HittableCollection objects;

    std::shared_ptr<Lambertian> red = std::make_shared<Lambertian>(Color(0.65f, 0.05f, 0.05f));
    std::shared_ptr<Lambertian> white = std::make_shared<Lambertian>(Color(0.73f, 0.73f, 0.73f));
    std::shared_ptr<Lambertian> green = std::make_shared<Lambertian>(Color(0.12f, 0.45f, 0.15f));
    std::shared_ptr<DiffuseLight> whiteLight = std::make_shared<DiffuseLight>(Color(15.0f, 15.0f, 15.0f));

    objects.Add(std::make_shared<YZRectangle>(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, green));
    objects.Add(std::make_shared<YZRectangle>(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, red));
    objects.Add(std::make_shared<XZRectangle>(213.0f, 343.0f, 227.0f, 332.0f, 554.0f, whiteLight));
    objects.Add(std::make_shared<XZRectangle>(0.0f, 555.0f, 0.0f, 555.0f, 0.0f, white));
    objects.Add(std::make_shared<XZRectangle>(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, white));
    objects.Add(std::make_shared<XYRectangle>(0.0f, 555.0f, 0.0f, 555.0f, 555.0f, white));

    std::shared_ptr<Hittable> box1 = std::make_shared<Box>(Vec3::Zero(), Vec3(165.0f, 330.0f, 165.0f), white);
    box1 = std::make_shared<RotateY>(box1, 15.0f);
    box1 = std::make_shared<Translate>(box1, Vec3(265.0f, 0.0f, 295.0f));
    objects.Add(box1);

    std::shared_ptr<Hittable> box2 = std::make_shared<Box>(Vec3::Zero(), Vec3(165.0f, 165.0f, 165.0f), white);
    box2 = std::make_shared<RotateY>(box2, -18.0f);
    box2 = std::make_shared<Translate>(box2, Vec3(130.0f, 0.0f, 65.0f));
    objects.Add(box2);

    return HittableCollection(std::make_shared<BVHNode>(objects, 0.0f, 1.0f));
}

int main() {
    std::srand((unsigned)std::time(NULL));

    // Image

    const int maxDepth = 50;
    int imageWidth = 400;
    float aspectRatio = 16.0f / 9.0f;
    int samplesPerPixel = 100;

    // World

    HittableCollection world;

    Vec3 lookFrom;
    Vec3 lookAt;
    float verticalFov = 40.0f;
    float aperture = 0.0f;
    Color backgroundColor;

    switch (3) {
        case 0:
            world = GetRandomScene();
            lookFrom = Vec3(13.0f, 2.0f, 3.0f);
            lookAt = Vec3::Zero();
            verticalFov = 20.0f;
            aperture = 0.1f;
            backgroundColor = Color(0.7f, 0.8f, 1.0f);
            break;

        case 1:
            world = GetTwoSpheresScene();
            lookFrom = Vec3(13.0f, 2.0f, 3.0f);
            lookAt = Vec3::Zero();
            verticalFov = 20.0f;
            backgroundColor = Color(0.7f, 0.8f, 1.0f);
            break;

        case 2:
            world = GetTwoPerlinSpheresScene();
            lookFrom = Vec3(13.0f, 2.0f, 3.0f);
            lookAt = Vec3::Zero();
            verticalFov = 20.0f;
            backgroundColor = Color(0.7f, 0.8f, 1.0f);
            break;

        case 3:
            world = GetEarthScene();
            lookFrom = Vec3(0.0f, 2.0f, 13.0f);
            lookAt = Vec3::Zero();
            verticalFov = 20.0f;
            backgroundColor = Color(0.7f, 0.8f, 1.0f);
            break;

        case 4:
            world = GetSimpleLightScene();
            samplesPerPixel = 400;
            backgroundColor = Color::Black();
            lookFrom = Vec3(26.0f, 3.0f, 6.0f);
            lookAt = Vec3(0.0f, 2.0f, 0.0f);
            verticalFov = 20.0f;
            break;

        case 5:
            world = GetCornellBoxScene();
            aspectRatio = 1.0f;
            imageWidth = 400;
            samplesPerPixel = 200;
            backgroundColor = Color::Black();
            lookFrom = Vec3(278.0f, 278.0f, -800.0f);
            lookAt = Vec3(278.0f, 278.0f, 0.0f);
            verticalFov = 40.0f;
            break;

        default:
            backgroundColor = Color::Black();
            break;
    }

    // Camera

    Vec3 vUp = Vec3::Up();
    float focusDistance = 10.0f;
    int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    Camera camera(lookFrom, lookAt, vUp, verticalFov, aspectRatio, aperture, focusDistance, 0.0f, 1.0f);

    // Render

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << '\n' << "255\n";

    for (int i = imageHeight - 1; i >= 0; i--) {
        std::cerr << "\nScanlines remaining: " << (i + 1) << ' ' << std::flush;
        for (int j = 0; j < imageWidth; j++) {
            Color pixelColor = Color::Black();
            for (int s = 0; s < samplesPerPixel; s++) {
                float u = (j + RandomFloat()) / (imageWidth - 1);
                float v = (i + RandomFloat()) / (imageHeight - 1);
                Ray ray = camera.GetRay(u, v);
                pixelColor += GetRayColor(ray, backgroundColor, world, maxDepth);
            }
            pixelColor.WritePPM(std::cout, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}
