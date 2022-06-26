#include "Box.h"
#include "AARectangle.h"
#include "BVHNode.h"
#include "Vec3.h"
#include "HittableCollection.h"

struct Material;
struct Ray;
struct HitRecord;

Box::Box(const Vec3& min, const Vec3& max, std::shared_ptr<Material> mat) {
	Min = min;
	Max = max;

	HittableCollection sides;

	sides.Add(std::make_shared<XYRectangle>(min.X, max.X, min.Y, max.Y, min.Z, mat));
	sides.Add(std::make_shared<XYRectangle>(min.X, max.X, min.Y, max.Y, max.Z, mat));

	sides.Add(std::make_shared<XZRectangle>(min.X, max.X, min.Z, max.Z, min.Y, mat));
	sides.Add(std::make_shared<XZRectangle>(min.X, max.X, min.Z, max.Z, max.Y, mat));

	sides.Add(std::make_shared<YZRectangle>(min.Y, max.Y, min.Z, max.Z, min.X, mat));
	sides.Add(std::make_shared<YZRectangle>(min.Y, max.Y, min.Z, max.Z, max.X, mat));

	Sides = HittableCollection(std::make_shared<BVHNode>(sides, 0.0f, 1.0f));
}

bool Box::Hit(const Ray& ray, float tMin, float tMax, HitRecord& hitRecord) const {
	return Sides.Hit(ray, tMin, tMax, hitRecord);
}
