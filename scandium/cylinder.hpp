#ifndef SCAN_CYLINDER_H
#define SCAN_CYLINDER_H

#include "shape.hpp"

class Cylinder : public Shape {
public:
	Cylinder(const Transform* ObjectToWorld, const Transform* WorldToObject, float radius, float zMin, float zMax) : Shape(ObjectToWorld, WorldToObject), radius(radius), zMin(zMin), zMax(zMax) {}

	bool Intersect(const Ray& r, float* tHit, Normal3f* normal) const;

private:
	const float radius, zMin, zMax;
};

bool Cylinder::Intersect(const Ray& r, float* tHit, Normal3f* normal) const {
	Ray ray = (*WorldToObject)(r);
	Point3f pHit;

	float dx = ray.d.x, dy = ray.d.y, dz = ray.d.z;
	float ox = ray.o.x, oy = ray.o.y, oz = ray.o.z;

	float a = dx * dx + dy * dy;
	float b = 2 * (dx * ox + dy * oy);
	float c = ox * ox + oy * oy - radius * radius;

	float t1, t2;
	if (!Quadratic(a, b, c, &t1, &t2)) {
		return false;
	}

	if (t1 > ray.timeMax || t2 <= 0) {
		return false;
	}

	float tShapeHit = t1;
	if (t1 <= 0) {
		tShapeHit = t2;
		if (tShapeHit > ray.timeMax) {
			return false;
		}
	}

	*tHit = (float)tShapeHit;
	pHit = ray(*tHit);
	*normal = Normal3f(pHit.x, pHit.y, pHit.z);
	return true;
}

#endif
