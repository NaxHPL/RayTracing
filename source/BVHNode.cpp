#include <algorithm>
#include <iostream>
#include "BVHNode.h"
#include "AABB.h"
#include "HitRecord.h"
#include "RTWeekend.h"
#include "Hittable.h"

struct Ray;

BVHNode::BVHNode(const std::vector<std::shared_ptr<Hittable>>& srcObjects,
                 size_t start,
                 size_t end,
                 float time0,
                 float time1) {

    size_t objSpan = end - start;

    if (objSpan == 1) {
        LeftChild = RightChild = srcObjects[start];
    }
    else if (objSpan == 2) {
        LeftChild = srcObjects[start];
        RightChild = srcObjects[start + 1];
    }
    else {
        Axis axis = static_cast<Axis>(RandomInt(0, 2));
        auto comparator =
            axis == Axis::X ? Hittable::BoxCompareX :
            axis == Axis::Y ? Hittable::BoxCompareY :
            Hittable::BoxCompareZ;

        auto objects = srcObjects; // Create a modifiable array of the source scene objects
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        size_t mid = objSpan / 2;

        LeftChild = std::make_shared<BVHNode>(objects, start, mid, time0, time1);
        RightChild = std::make_shared<BVHNode>(objects, mid, end, time0, time1);
    }

    AABB boxLeft, boxRight;

    if (!LeftChild->BoundingBox(time0, time1, boxLeft) || !RightChild->BoundingBox(time0, time1, boxRight)) {
        std::cerr << "No bounding box in BVHNode constructor.\n";
    }

    Box = AABB::SurroundingBox(boxLeft, boxRight);
}

bool BVHNode::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
    if (!Box.Hit(ray, tMin, tMax)) {
        return false;
    }

    bool hitLeft = LeftChild->Hit(ray, tMin, tMax, hitRecord);
    bool hitRight = RightChild->Hit(ray, tMin, hitLeft ? hitRecord.T : tMax, hitRecord);

    return hitLeft || hitRight;
}

bool BVHNode::BoundingBox(float time0, float time1, AABB& aabbOut) const {
    aabbOut = Box;
    return false;
}
