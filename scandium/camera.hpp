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
				bool hit = false;
				float tHit;
				Normal3f normal;
				Vector3f L = -scene.Lights->dir;
				
				for (int x = 0; x < scene.Shapes.size(); x++) {
					if (scene.Shapes[x]->Intersect(ray, &tHit, &normal)) {
						hit = true;
						ray.timeMax = tHit;
					}
				}

				if (hit) {
					Vector3f c = scene.Lights->color * std::max(0.0f, Dot(normal, L)) * 0.18f / Pi * scene.Lights->intensity;
					(*pixel++) = Vector3f(c.x, c.y, c.z);
					//(*pixel++) = Vector3f(255, 0, 0);
				}
				else {
					(*pixel++) = Vector3f(0, 0, 0);
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
