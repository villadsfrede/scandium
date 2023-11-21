#ifndef SCAN_RAY_H
#define SCAN_RAY_H

#include "vector.hpp"

class Ray {
public:
	Ray(Point3f o, Vector3f d, float time = 0.f) : o(o), d(d), time(time) {}

	Point3f o;
	Vector3f d;
	float time;
};

#endif
