#ifndef SCAN_SHAPE_H
#define SCAN_SHAPE_H

#include "vector.hpp"
#include "ray.hpp"
#include "transform.hpp"

// Form superclass
class Shape {
public:
	Shape(const Transform* ObjectToWorld, const Transform* WorldToObject, const int type) : ObjectToWorld(ObjectToWorld), WorldToObject(WorldToObject), type(type) {}

	virtual bool Intersect(const Ray& ray, float* tHit, Normal3f* normal, float tNear) const = 0;

	// Transformation fra objekt til verden og verden til objekt
	const Transform *ObjectToWorld, *WorldToObject;
	const int type;
};

#endif
