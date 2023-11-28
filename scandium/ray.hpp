#ifndef SCAN_RAY_H
#define SCAN_RAY_H

#include "scan.h"
#include "vector.hpp"

class Ray {
public:
	Ray(Point3f o, Vector3f d, float time = 0.0f, float timeMax = Infinity) : o(o), d(d), time(time), timeMax(timeMax) {}

	Point3f o;
	Vector3f d;
	float time;
	mutable float timeMax;
};

#endif
