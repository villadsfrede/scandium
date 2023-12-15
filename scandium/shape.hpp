#ifndef SCAN_SHAPE_H
#define SCAN_SHAPE_H

#include "vector.hpp"
#include "ray.hpp"
#include "transform.hpp"

class Shape {
public:
	Shape(const Transform* ObjectToWorld, const Transform* WorldToObject, const int type) : ObjectToWorld(ObjectToWorld), WorldToObject(WorldToObject), type(type) {}

	virtual bool Intersect(const Ray& ray, float* tHit, Normal3f* normal) const = 0;

	const Transform *ObjectToWorld, *WorldToObject;
	const int type;
};

#endif
