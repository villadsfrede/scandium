#ifndef SCAN_LIGHT_H
#define SCAN_LIGHT_H

#include "vector.hpp"
#include "transform.hpp"

class Light {
public:
	Light(const Transform *LTW, const Vector3f color, const float intensity) : LTW(LTW), color(color), intensity(intensity) {}

	const Transform *LTW;
	const Vector3f color;
	const float intensity;
};

class DistantLight : public Light {
public:
	DistantLight(const Transform* LTW, const Vector3f color, const float intensity, const Vector3f dir) : Light(LTW, color, intensity), dir((*LTW)(dir)) {}

	const Vector3f dir;
};

#endif
