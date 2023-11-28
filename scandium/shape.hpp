#ifndef SCAN_SHAPE_H
#define SCAN_SHAPE_H

#include "ray.hpp"
#include "transform.hpp"

class Shape {
public:
	Shape(const Transform* ObjectToWorld, const Transform* WorldToObject);

	virtual bool Intersect(const Ray& ray, float* tHis) const = 0;

	const Transform* ObjectToWorld, WorldToObject;
};

#endif
