#include "BVHNode.h"
#include "AABB.h"
#include "HitRecord.h"
#include "RTWeekend.h"

struct Ray;

BVHNode::BVHNode(const std::vector<std::shared_ptr<IHittable>>& srcObjects,
                 size_t start,
                 size_t end,
                 float time0,
                 float time1) {


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
