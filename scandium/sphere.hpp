#ifndef SCAN_SPHERE_H
#define SCAN_SPHERE_H

#include <iostream>
#include "ray.hpp"
#include "shape.hpp"

class Sphere : public Shape {
public:
	Sphere(const Transform* ObjectToWorld, const Transform* WorldToObject, const int type, float radius) : Shape(ObjectToWorld, WorldToObject, type), radius(radius) {}

	bool Intersect(const Ray& r, float* tHit, Normal3f* normal, float tNear) const;

	// Kugle privat data
private:
	const float radius;
};

// Kugle og stråle skæringsfunktion
bool Sphere::Intersect(const Ray& r, float* tHit, Normal3f* normal, float tNear) const {
	Ray ray = (*WorldToObject)(r);
	Point3f pHit;

	//std::cout << ray.d.x << std::endl;

	float dx = ray.d.x, dy = ray.d.y, dz = ray.d.z;
	float ox = ray.o.x, oy = ray.o.y, oz = ray.o.z;

	//std::cout << dx << ' ' << dy << ' ' << dz << std::endl;
	//std::cout << ox << ' ' << oy << ' ' << oz << std::endl;

	float a = dx * dx + dy * dy + dz * dz;
	float b = 2 * (dx * ox + dy * oy + dz * oz);
	float c = ox * ox + oy * oy + oz * oz - radius * radius;

	//std::cout << a << ' ' << b << ' ' << c << std::endl;

	float t1, t2;
	if (!Quadratic(a, b, c, &t1, &t2)) {
		return false;
	}
	
	//std::cout << t1 << ' ' << t2 << std::endl;
	
	if (t1 > tNear || t2 <= 0) {
		return false;
	}

	float tShapeHit = t1;
	if (t1 <= 0) {
		tShapeHit = t2;
		if (tShapeHit > tNear) {
			return false;
		}
	}

	*tHit = (float)tShapeHit;
	pHit = ray(*tHit);
	*normal = Normal3f(pHit.x, pHit.y, pHit.z);
	return true;
}

#endif
