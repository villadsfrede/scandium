#ifndef SCAN_TRIANGLEMESH_H
#define SCAN_TRIANGLEMESH_H

#include "shape.hpp"

class TriangleMesh : public Shape {
public:
	TriangleMesh(const Transform* ObjectToWorld, const Transform* WorldToObject, const int type, std::vector<Vector3f>* vertices, std::vector<int>* verticesIndex) : Shape(ObjectToWorld, WorldToObject, type), vertices(vertices), verticesIndex(verticesIndex) {}

	bool Intersect(const Ray& r, float* tHit, Normal3f* normal, float tNear) const;

	// Public data
	std::vector<Vector3f>* vertices;
	std::vector<int>* verticesIndex;
};

// Intersect of ray and triangle mesh
bool TriangleMesh::Intersect(const Ray& r, float* tHit, Normal3f* normal, float tNear) const {
	Ray ray = (*WorldToObject)(r);

	Vector3 o = Vector3f(ray.o.x, ray.o.y, ray.o.z);

	int faceNum = verticesIndex->size() / 3;
	
	// For each triangle in mesh
	for (int i = 0; i < faceNum; i++) {
		Vector3f v0 = vertices->at((verticesIndex->at(i * 3)));
		Vector3f v1 = vertices->at((verticesIndex->at(i * 3 + 1)));
		Vector3f v2 = vertices->at((verticesIndex->at(i * 3 + 2)));

		Vector3f v0v1 = v1 - v0;
		Vector3f v0v2 = v2 - v0;

		Vector3f n = Cross(v0v1, v0v2) / Length(Cross(v0v1, v0v2));

		// Ray og plane er parralle
		if (Dot(n, ray.d) == 0) {
			return false;
		}

		float d = Dot(n, v0);
		float t = (d - Dot(n, o)) / Dot(n, ray.d);

		if (t < 0 || t > tNear) {
			return false;
		}

		Vector3f P = o + ray.d * t;

		// edge 0
		Vector3f edge0 = v1 - v0;
		Vector3f Pv0 = P - v0;
		if (Dot(Cross(edge0, Pv0), n) < 0) {
			return false;
		}

		// edge 1
		Vector3f edge1 = v2 - v1;
		Vector3f Pv1 = P - v1;
		if (Dot(Cross(edge1, Pv1), n) < 0) {
			return false;
		}

		// edge 2
		Vector3f edge2 = v0 - v2;
		Vector3f Pv2 = P - v2;
		if (Dot(Cross(edge0, Pv2), n) < 0) {
			return false;
		}

		*tHit = (float)t;
		*normal = Normal3f(n.x, n.y, n.z);
		return true;	
	}
}

#endif