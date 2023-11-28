#ifndef SCAN_SHAPE_H
#define SCAN_SHAPE_H

#include "transform.hpp"

class Shape {
public:
	Shape(const Transform* Object) {}

	const Transform* ObjectToWorld;
};

#endif
