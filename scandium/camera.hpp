#ifndef SCAN_CAMERA_H
#define SCAN_CAMERA_H

#include <cmath>
#include "ray.hpp"
#include "transform.hpp"
#include "image.hpp"
#include "scene.hpp"

class Camera {
public:
	Camera(const Transform* CTW, const Scene scene, const int width, const int height, const float fov) : CTW(CTW), scene(scene), width(width), height(height), fov(fov) {}
	virtual Ray GenerateRay(int ImageX, int ImageY) = 0;
	
	void Render() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Ray ray = GenerateRay(j, i);

				float tHit = 0;

				if (scene.Shapes[0]->Intersect(ray, &tHit)) {
					*(pixels++) = Vector3f(255, 0, 0);
				}
				else {
					*(pixels++) = Vector3f(0, 0, 0);
				}
			}
		}
		save(width, height, film);
	}

	const Transform* CTW;
	const Scene scene;
	const Point3f origin = (*CTW)(Point3f(0,0,0));
	const int width;
	const int height;
	const float fov;
	Vector3f* film = new Vector3f[width * height];
	Vector3f* pixels = film;
};


class ProjectiveCamera : public Camera {
public:
	ProjectiveCamera(const Transform* CTW, const Scene scene, int width, int height, float fov) : Camera(CTW, scene, width, height, fov), AspectRatio(width / height), scale(tan(fov * 0.5)) {}

	Ray GenerateRay(int ImageX, int ImageY) {
		float x = (2 * (ImageX + 0.5) / width) * AspectRatio * scale;
		float y = (1 - 2 * (ImageY + 0.5) / height) * scale;
		Vector3f dir = Normalize((*CTW)(Vector3f(x, y, -1)));
		return Ray(origin, dir);
	}
	
	float AspectRatio;
	float scale;
};

#endif
