#ifndef SCAN_LIGHT_H
#define SCAN_LIGHT_H

#include "vector.hpp"
#include "transform.hpp"

// Lys superclass
class Light {
public:
	Light(const Transform *LTW, const Vector3f color, const float intensity) : LTW(LTW), color(color), intensity(intensity) {}

	const Transform *LTW;
	const Vector3f color;
	const float intensity;
};

// Class til lys langt væk (f.eks. solen)
class DistantLight : public Light {
public:
	DistantLight(const Transform* LTW, const Vector3f color, const float intensity, const Vector3f dir) : Light(LTW, color, intensity), dir((*LTW)(dir)) {}

	const Vector3f dir;
};

#endif
