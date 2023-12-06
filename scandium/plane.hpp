#ifndef SCAN_PLANE_H
#define SCAN_PLANE_H

#include "shape.hpp"

class Plane : public Shape {
public:
	Plane(const Transform* ObjectToWorld, const Transform* WorldToObject, const float height) : Shape(ObjectToWorld, WorldToObject), height(height) {}

	bool Intersect(const Ray& r, float* tHit, Normal3f* normal) const;

private:
	const float height;
};

bool Plane::Intersect(const Ray& r, float* tHit, Normal3f* normal) const {
	Ray ray = (*WorldToObject)(r);
	Point3f pHit;
	
	return false;
}

#endif
