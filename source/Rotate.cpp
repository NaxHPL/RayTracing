#include <cmath>
#include "Rotate.h"
#include "Ray.h"
#include "HitRecord.h"
#include "RTWeekend.h"
#include "Vec3.h"

void Rotation::Init(std::shared_ptr<Hittable> hittable, float angle) {
    Object = hittable;

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

                Vec3 testVector = Rotate(x, y, z);

                for (int a = 0; a < 3; a++) {
                    Axis axis = static_cast<Axis>(a);
                    min[axis] = std::fminf(min[axis], testVector[axis]);
                    max[axis] = std::fmaxf(max[axis], testVector[axis]);
                }
            }
        }
    }

    BBox = AABB(min, max);
}

bool Rotation::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
    Vec3 rotatedOrigin = Rotate(ray.Origin);
    Vec3 rotatedDirection = Rotate(ray.Direction);

    Ray rotatedRay(rotatedOrigin, rotatedDirection, ray.Time);

    if (!Object->Hit(rotatedRay, tMin, tMax, hitRecord)) {
        return false;
    }

    Vec3 rotatedPoint = Rotate(hitRecord.Point);
    Vec3 rotatedNormal = Rotate(hitRecord.Normal);

    hitRecord.Point = rotatedPoint;
    hitRecord.SetFaceNormal(rotatedDirection, rotatedNormal);

    return true;
}

//RotateY::RotateY(std::shared_ptr<Hittable> hittable, float angle) : Object(hittable) {
//    float radians = DegreesToRadians(angle);
//
//    SinTheta = std::sinf(radians);
//    CosTheta = std::cosf(radians);
//
//    HasBox = hittable->BoundingBox(0.0f, 1.0f, BBox);
//
//    Vec3 min(INF_F, INF_F, INF_F);
//    Vec3 max(-INF_F, -INF_F, -INF_F);
//
//    for (int i = 0; i < 2; i++) {
//        for (int j = 0; j < 2; j++) {
//            for (int k = 0; k < 2; k++) {
//                float x = i * BBox.Maximum.X + (1 - i) * BBox.Minimum.X;
//                float y = j * BBox.Maximum.Y + (1 - j) * BBox.Minimum.Y;
//                float z = k * BBox.Maximum.Z + (1 - k) * BBox.Minimum.Z;
//
//                float newX = CosTheta * x + SinTheta * z;
//                float newZ = -SinTheta * x + CosTheta * z;
//
//                Vec3 testVec(newX, y, newZ);
//
//                for (int a = 0; a < 3; a++) {
//                    Axis axis = static_cast<Axis>(a);
//                    min[axis] = std::fminf(min[axis], testVec[axis]);
//                    max[axis] = std::fmaxf(max[axis], testVec[axis]);
//                }
//            }
//        }
//    }
//
//    BBox = AABB(min, max);
//}
//
//bool RotateY::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
//    Vec3 rotatedOrigin = ray.Origin;
//    rotatedOrigin.X = CosTheta * ray.Origin.X - SinTheta * ray.Origin.Z;
//    rotatedOrigin.Z = SinTheta * ray.Origin.X + CosTheta * ray.Origin.Z;
//
//    Vec3 rotatedDirection = ray.Direction;
//    rotatedDirection.X = CosTheta * ray.Direction.X - SinTheta * ray.Direction.Z;
//    rotatedDirection.Z = SinTheta * ray.Direction.X + CosTheta * ray.Direction.Z;
//
//    Ray rotatedRay(rotatedOrigin, rotatedDirection, ray.Time);
//
//    if (!Object->Hit(rotatedRay, tMin, tMax, hitRecord)) {
//        return false;
//    }
//
//    Vec3 rotatedPoint = hitRecord.Point;
//    rotatedPoint.X = CosTheta * hitRecord.Point.X + SinTheta * hitRecord.Point.Z;
//    rotatedPoint.Z = -SinTheta * hitRecord.Point.X + CosTheta * hitRecord.Point.Z;
//
//    Vec3 rotatedNormal = hitRecord.Normal;
//    rotatedNormal.X = CosTheta * hitRecord.Normal.X + SinTheta * hitRecord.Normal.Z;
//    rotatedNormal.Z = -SinTheta * hitRecord.Normal.X + CosTheta * hitRecord.Normal.Z;
//
//    hitRecord.Point = rotatedPoint;
//    hitRecord.SetFaceNormal(rotatedDirection, rotatedNormal);
//
//    return true;
//}
//
//RotateX::RotateX(std::shared_ptr<Hittable> hittable, float angle) : Object(hittable) {
//    float radians = DegreesToRadians(angle);
//
//    SinTheta = std::sinf(radians);
//    CosTheta = std::cosf(radians);
//
//    HasBox = hittable->BoundingBox(0.0f, 1.0f, BBox);
//
//    Vec3 min(INF_F, INF_F, INF_F);
//    Vec3 max(-INF_F, -INF_F, -INF_F);
//
//    for (int i = 0; i < 2; i++) {
//        for (int j = 0; j < 2; j++) {
//            for (int k = 0; k < 2; k++) {
//                float x = i * BBox.Maximum.X + (1 - i) * BBox.Minimum.X;
//                float y = j * BBox.Maximum.Y + (1 - j) * BBox.Minimum.Y;
//                float z = k * BBox.Maximum.Z + (1 - k) * BBox.Minimum.Z;
//
//                float newY = CosTheta * y - SinTheta * z; // changed
//                float newZ = SinTheta * y + CosTheta * z; // changed
//
//                Vec3 testVec(x, newY, newZ); // changed
//
//                for (int a = 0; a < 3; a++) {
//                    Axis axis = static_cast<Axis>(a);
//                    min[axis] = std::fminf(min[axis], testVec[axis]);
//                    max[axis] = std::fmaxf(max[axis], testVec[axis]);
//                }
//            }
//        }
//    }
//
//    BBox = AABB(min, max);
//}
//
//bool RotateX::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
//    Vec3 rotatedOrigin = ray.Origin;
//    rotatedOrigin.Y = CosTheta * ray.Origin.Y + SinTheta * ray.Origin.Z; // changed
//    rotatedOrigin.Z = -SinTheta * ray.Origin.Y + CosTheta * ray.Origin.Z; // changed
//
//    Vec3 rotatedDirection = ray.Direction;
//    rotatedDirection.Y = CosTheta * ray.Direction.Y + SinTheta * ray.Direction.Z; // changed
//    rotatedDirection.Z = -SinTheta * ray.Direction.Y + CosTheta * ray.Direction.Z; // changed
//
//    Ray rotatedRay(rotatedOrigin, rotatedDirection, ray.Time);
//
//    if (!Object->Hit(rotatedRay, tMin, tMax, hitRecord)) {
//        return false;
//    }
//
//    Vec3 rotatedPoint = hitRecord.Point;
//    rotatedPoint.Y = CosTheta * hitRecord.Point.Y - SinTheta * hitRecord.Point.Z; // changed
//    rotatedPoint.Z = SinTheta * hitRecord.Point.Y + CosTheta * hitRecord.Point.Z; // changed
//
//    Vec3 rotatedNormal = hitRecord.Normal;
//    rotatedNormal.Y = CosTheta * hitRecord.Normal.Y - SinTheta * hitRecord.Normal.Z; // changed
//    rotatedNormal.Z = SinTheta * hitRecord.Normal.Y + CosTheta * hitRecord.Normal.Z; // changed
//
//    hitRecord.Point = rotatedPoint;
//    hitRecord.SetFaceNormal(rotatedDirection, rotatedNormal);
//
//    return true;
//}
//
//RotateZ::RotateZ(std::shared_ptr<Hittable> hittable, float angle) : Object(hittable) {
//    float radians = DegreesToRadians(angle);
//
//    SinTheta = std::sinf(radians);
//    CosTheta = std::cosf(radians);
//
//    HasBox = hittable->BoundingBox(0.0f, 1.0f, BBox);
//
//    Vec3 min(INF_F, INF_F, INF_F);
//    Vec3 max(-INF_F, -INF_F, -INF_F);
//
//    for (int i = 0; i < 2; i++) {
//        for (int j = 0; j < 2; j++) {
//            for (int k = 0; k < 2; k++) {
//                float x = i * BBox.Maximum.X + (1 - i) * BBox.Minimum.X;
//                float y = j * BBox.Maximum.Y + (1 - j) * BBox.Minimum.Y;
//                float z = k * BBox.Maximum.Z + (1 - k) * BBox.Minimum.Z;
//
//                float newX = CosTheta * x - SinTheta * y; // changed
//                float newY = SinTheta * x + CosTheta * y; // changed
//
//                Vec3 testVec(newX, newY, z); // changed
//
//                for (int a = 0; a < 3; a++) {
//                    Axis axis = static_cast<Axis>(a);
//                    min[axis] = std::fminf(min[axis], testVec[axis]);
//                    max[axis] = std::fmaxf(max[axis], testVec[axis]);
//                }
//            }
//        }
//    }
//
//    BBox = AABB(min, max);
//}
//
//bool RotateZ::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
//    Vec3 rotatedOrigin = ray.Origin;
//    rotatedOrigin.X = CosTheta * ray.Origin.X + SinTheta * ray.Origin.Y; // changed
//    rotatedOrigin.Y = -SinTheta * ray.Origin.X + CosTheta * ray.Origin.Y; // changed
//
//    Vec3 rotatedDirection = ray.Direction;
//    rotatedDirection.X = CosTheta * ray.Direction.X + SinTheta * ray.Direction.Y; // changed
//    rotatedDirection.Y = -SinTheta * ray.Direction.X + CosTheta * ray.Direction.Y; // changed
//
//    Ray rotatedRay(rotatedOrigin, rotatedDirection, ray.Time);
//
//    if (!Object->Hit(rotatedRay, tMin, tMax, hitRecord)) {
//        return false;
//    }
//
//    Vec3 rotatedPoint = hitRecord.Point;
//    rotatedPoint.X = CosTheta * hitRecord.Point.X - SinTheta * hitRecord.Point.Y; // changed
//    rotatedPoint.Y = SinTheta * hitRecord.Point.X + CosTheta * hitRecord.Point.Y; // changed
//
//    Vec3 rotatedNormal = hitRecord.Normal;
//    rotatedNormal.X = CosTheta * hitRecord.Normal.X - SinTheta * hitRecord.Normal.Y; // changed
//    rotatedNormal.Y = SinTheta * hitRecord.Normal.X + CosTheta * hitRecord.Normal.Y; // changed
//
//    hitRecord.Point = rotatedPoint;
//    hitRecord.SetFaceNormal(rotatedDirection, rotatedNormal);
//
//    return true;
//}