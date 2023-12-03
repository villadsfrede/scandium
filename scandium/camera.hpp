#ifndef SCAN_CAMERA_H
#define SCAN_CAMERA_H

#include <cmath>
#include "ray.hpp"
#include "transform.hpp"

class Camera {
public:
	Camera(const Transform* CTW, int width, int height, float fov) : CTW(CTW), width(width), height(height), fov(fov) {}
	virtual Ray GenerateRay(int ImageX, int ImageY);

	const Transform* CTW;
	int width;
	int height;
	float fov;
	Vector3f* film = new Vector3f[width * height];
};

class ProjectiveCamera : public Camera {
public:
	ProjectiveCamera(const Transform* CTW, int width, int height, float fov) : Camera(CTW, width, height, fov), AspectRatio(width / height), scale(tan(fov * 0.5)) {}

	Ray GenerateRay(int ImageX, int ImageY) {
		float x = (2 * (ImageX + 0.5) / width) * AspectRatio * scale;
		float y = (1 - 2 * (ImageY + 0.5) / height) * scale;
		Vector3f dir = (*CTW)(Vector3f(x, y, -1));
	}

	float AspectRatio;
	float scale;
};

#endif
