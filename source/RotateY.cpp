#include <cmath>
#include "RotateY.h"
#include "Ray.h"
#include "HitRecord.h"
#include "RTWeekend.h"
#include "Vec3.h"

RotateY::RotateY(std::shared_ptr<Hittable> hittable, float angle) : Object(hittable) {
    float radians = DegreesToRadians(angle);

    SinTheta = std::sinf(radians);
    CosTheta = std::cosf(radians);

    HasBox = hittable->BoundingBox(0.0f, 1.0f, BBox);

    Vec3 min(INF_F, INF_F, INF_F);
    Vec3 max(-INF_F, -INF_F, -INF_F);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                float x = i * BBox.Maximum.X + (1 - i) * BBox.Minimum.X;
                float y = j * BBox.Maximum.Y + (1 - j) * BBox.Minimum.Y;
                float z = k * BBox.Maximum.Z + (1 - k) * BBox.Minimum.Z;

                float newX = CosTheta * x + SinTheta * z;
                float newZ = -SinTheta * x + CosTheta * z;

                Vec3 testVec(newX, y, newZ);

                for (int a = 0; a < 3; a++) {
                    Axis axis = static_cast<Axis>(a);
                    min[axis] = std::fminf(min[axis], testVec[axis]);
                    max[axis] = std::fmaxf(max[axis], testVec[axis]);
                }
            }
        }
    }

    BBox = AABB(min, max);
}

bool RotateY::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
    Vec3 rotatedOrigin = ray.Origin;
    rotatedOrigin.X = CosTheta * ray.Origin.X - SinTheta * ray.Origin.Z;
    rotatedOrigin.Z = SinTheta * ray.Origin.X + CosTheta * ray.Origin.Z;

    Vec3 rotatedDirection = ray.Direction;
    rotatedDirection.X = CosTheta * ray.Direction.X - SinTheta * ray.Direction.Z;
    rotatedDirection.Z = SinTheta * ray.Direction.X + CosTheta * ray.Direction.Z;

    Ray rotatedRay(rotatedOrigin, rotatedDirection, ray.Time);

    if (!Object->Hit(rotatedRay, tMin, tMax, hitRecord)) {
        return false;
    }

    Vec3 rotatedPoint = hitRecord.Point;
    rotatedPoint.X = CosTheta * hitRecord.Point.X + SinTheta * hitRecord.Point.Z;
    rotatedPoint.Z = -SinTheta * hitRecord.Point.X + CosTheta * hitRecord.Point.Z;

    Vec3 rotatedNormal = hitRecord.Normal;
    rotatedNormal.X = CosTheta * hitRecord.Normal.X + SinTheta * hitRecord.Normal.Z;
    rotatedNormal.Z = -SinTheta * hitRecord.Normal.X + CosTheta * hitRecord.Normal.Z;

    hitRecord.Point = rotatedPoint;
    hitRecord.SetFaceNormal(rotatedDirection, rotatedNormal);

    return true;
}
