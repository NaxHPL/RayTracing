#include <cmath>
#include "Camera.h"
#include "RTWeekend.h"
#include "Ray.h"

Camera::Camera(Vec3 lookFrom,
               Vec3 lookAt,
               Vec3 vUp,
               float verticalFov,
               float aspectRatio,
               float aperture,
               float focusDistance,
               float time0,
               float time1) {

    float theta = DegreesToRadians(verticalFov);
    float h = std::tanf(theta / 2.0f);
    float viewportHeight = 2.0f * h;
    float viewportWidth = viewportHeight * aspectRatio;

    w = (lookFrom - lookAt).Normalized();
    u = Vec3::Cross(vUp, w).Normalized();
    v = Vec3::Cross(w, u);

    origin = lookFrom;
    horizontal = focusDistance * viewportWidth * u;
    vertical = focusDistance * viewportHeight * v;
    lowerLeftCorner = origin - horizontal / 2.0f - vertical / 2.0f - focusDistance * w;
    lensRadius = aperture / 2.0f;
    t0 = time0;
    t1 = time1;
}

Ray Camera::GetRay(float s, float t) const {
    Vec3 randInDisk = Vec3::RandomInUnitDisk() * lensRadius;
    Vec3 offset = u * randInDisk.X + v * randInDisk.Y;

    return Ray(
        origin + offset,
        lowerLeftCorner + s * horizontal + t * vertical - origin - offset,
        RandomFloat(t0, t1)
    );
}
