#include <cmath>
#include <utility>
#include "AABB.h"
#include "Ray.h"

bool AABB::Hit(const Ray& ray, float tMin, float tMax) const {
	for (int c = 0; c < 3; c++) {
		float invD = 1.0f / ray.Direction[c];

		float t0 = (Minimum[c] - ray.Origin[c]) * invD;
		float t1 = (Maximum[c] - ray.Origin[c]) * invD;

		if (invD < 0.0f) {
			std::swap(t0, t1);
		}

		tMin = t0 > tMin ? t0 : tMin;
		tMax = t1 < tMax ? t1 : tMax;

		if (tMax <= tMin) {
			return false;
		}
	}

	return true;
}
