#include <iostream>
#include "math.hpp"
#include "vector.hpp"
#include "ray.hpp"
#include "transform.hpp"

Point3f p = Point3f(2.0f, 1.0f, 1.0f);

float mat[4][4] = { {1,0,0,4}, {0,1,0,0}, {0,0,1,2}, {0,0,0,1} };

SquareMatrix<4> m;

Transform t = Transform(mat);

Point3f p2 = t(p);

int main() {
	std::cout << p2.z << std::endl;

	return 0;
}