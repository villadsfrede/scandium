#ifndef SCAN_CAMERA_H
#define SCAN_CAMERA_H

#include <cmath>
#include "scan.h"
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
				(*pixel++) = castRay(ray, 0);
			}
		}
		save(width, height, film);
	}

	Vector3f castRay(Ray& ray, int depth) {
		bool hit = false;
		float tHit;
		Normal3f normal;
		Vector3f L = -scene.Lights->dir;
		Vector3f hColor = Vector3f(0, 0, 0);
		int type;

		for (int x = 0; x < scene.Shapes.size(); x++) {
			if (scene.Shapes[x]->Intersect(ray, &tHit, &normal)) {
				hit = true;
				ray.timeMax = tHit;
				type = scene.Shapes[x]->type;
			}
		}

		if (hit) {
			if (type == 0) {
				hColor = scene.Lights->color * std::max(0.0f, Dot(normal, L)) * 0.18f / Pi * scene.Lights->intensity;
			}
			if (type == 1) {
				if (depth < 10) {
					Point3f pHit = ray(tHit);
					ray.o = Point3f(pHit.x + normal.x, pHit.y + normal.y, pHit.z + normal.z);
					ray.d = Reflect(Normalize(ray.d), Vector3f(normal.x, normal.y, normal.z));
					hColor += castRay(ray, depth + 1) * 0.8;
				}
			}
		}

		return hColor;
	}

	const Transform* CTW;
	const Scene scene;
	const Point3f origin = (*CTW)(Point3f(0,0,0));
	const int width;
	const int height;
	const float fov;
	Vector3f* film = new Vector3f[width * height];
	Vector3f* pixel = film;
};


class ProjectiveCamera : public Camera {
public:
	ProjectiveCamera(const Transform* CTW, const Scene scene, int width, int height, float fov) : Camera(CTW, scene, width, height, fov), AspectRatio(width / height), scale(tan(fov * 0.5)) {}

	Ray GenerateRay(int ImageX, int ImageY) {
		float x = (2 * (ImageX + 0.5) / width - 1) * AspectRatio * scale;
		float y = (1 - 2 * (ImageY + 0.5) / height) * scale;
		Vector3f dir = Normalize((*CTW)(Vector3f(x, y, -1)));
		return Ray(origin, dir);
	}
	
	float AspectRatio;
	float scale;
};

#endif
