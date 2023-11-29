#include <iostream>
#include "math.hpp"
#include "vector.hpp"
#include "ray.hpp"
#include "transform.hpp"
#include "shape.hpp"
#include "sphere.hpp"

float tn[4][4] = { {1,0,0,4},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
float it[4][4] = { {1,0,0,-4},{0,1,0,0},{0,0,1,0},{0,0,0,1} };

const Transform t1 = Transform(tn);
const Transform t2 = Transform(it);

Sphere s = Sphere(&t1, &t2, 4);

Point3f o = Point3f(0.0f, 0.0f, 0.0f);
Vector3f d = Vector3f(5.0f, 0.0f, 0.0f);

Ray r = Ray(o, d);

float tHit;

int main() {
	std::cout << s.Intersect(r, &tHit) << std::endl;
	std::cout << tHit << std::endl;
	return 0;
}