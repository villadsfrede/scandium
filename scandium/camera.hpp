#ifndef SCAN_CAMERA_H
#define SCAN_CAMERA_H

#include <cmath>
#include "scan.h"
#include "ray.hpp"
#include "transform.hpp"
#include "image.hpp"
#include "scene.hpp"

// Kamera superclass
class Camera {
public:
	Camera(const Transform* CTW, const Scene scene, const int width, const int height, const float fov) : CTW(CTW), scene(scene), width(width), height(height), fov(fov) {}
	virtual Ray GenerateRay(int ImageX, int ImageY) = 0;
	
	// Funktion til at generer billedet
	void Render() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Ray ray = GenerateRay(j, i);
				(*pixel++) = castRay(ray, 0);
			}
		}
		save(width, height, film);
	}

	// Funktion til at udregne skæring og farve
	Vector3f castRay(Ray& ray, int depth) {
		bool hit = false;
		float tHit;
		Normal3f normal;
		Vector3f L = -scene.Lights->dir;
		Vector3f hColor = Vector3f(0, 0, 0);
		int type;
		float tNear = Infinity;

		// Hvis funktion har kaldt sig selv (rekursion) mere end 10 gange returnere den baggrundsfarven.
		if (depth > 10) {
			return hColor;
		}

		// Test skæring mellem hvert objekt og stråle
		for (int x = 0; x < scene.Shapes.size(); x++) {
			if (scene.Shapes[x]->Intersect(ray, &tHit, &normal, tNear)) {
				tNear = tHit;
				hit = true;
				ray.timeMax = tHit;
				type = scene.Shapes[x]->type;
			}
		}

		if (hit) {
			// Diffust materiale
			if (type == 0) {
				hColor = scene.Lights->color * std::max(0.0f, Dot(normal, L)) * 0.05f  * scene.Lights->intensity;
			}
			// Refleksivt materiale
			if (type == 1) {
				Point3f pHit = ray(tHit);
				ray.o = Point3f(pHit.x + normal.x, pHit.y + normal.y, pHit.z + normal.z);
				ray.d = Reflect(Normalize(ray.d), Vector3f(normal.x, normal.y, normal.z));
				hColor += castRay(ray, depth + 1) * 0.8;
			}
			// Refraktivt materiale
			if (type == 2) {
				Vector3f n = Vector3f(normal.x, normal.y, normal.z);
				float cosi = Clamp(-1, 1, Dot(ray.d, n));
				float etai = 1;
				float etat = 1.3;
				if (cosi < 0) {
					cosi = -cosi;
				}
				else {
					std::swap(etai, etat);
					n = -n;
				}
				float eta = etai / etat;
				float k = 1 - eta * eta * (1 - cosi * cosi);
				ray.o = ray(tHit);
				ray.d = ray.d + n * (eta * cosi - std::sqrt(k));
				if (k > 0) {
					hColor += castRay(ray, depth + 1);
				}
			}
		}

		return hColor;
	}

	// Kamera data
	const Transform* CTW;
	const Scene scene;
	const Point3f origin = (*CTW)(Point3f(0,0,0));
	const int width;
	const int height;
	const float fov;
	Vector3f* film = new Vector3f[width * height];
	Vector3f* pixel = film;
};

// Projektiv kamera subclass
class ProjectiveCamera : public Camera {
public:
	ProjectiveCamera(const Transform* CTW, const Scene scene, int width, int height, float fov) : Camera(CTW, scene, width, height, fov), AspectRatio(width / height), scale(tan(fov * 0.5)) {}

	// Generation af primærstråle
	Ray GenerateRay(int ImageX, int ImageY) {
		float x = (2 * (ImageX + 0.5) / width - 1) * AspectRatio * scale;
		float y = (1 - 2 * (ImageY + 0.5) / height) * scale;
		Vector3f dir = Normalize((*CTW)(Vector3f(x, y, -1)));
		return Ray(origin, dir);
	}
	
	// Projekttiv kamera data
	float AspectRatio;
	float scale;
};

#endif
