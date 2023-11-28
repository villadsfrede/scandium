#include <iostream>
#include "math.hpp"
#include "vector.hpp"
#include "ray.hpp"
#include "transform.hpp"
#include "sphere.hpp"

float tn[4][4] = { {1,0,0,4},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
float it[4][4] = { {1,0,0,-4},{0,1,0,0},{0,0,1,0},{0,0,0,1} };

Transform t1 = Transform(tn);
Transform t2 = Transform(it);

int main() {
	return 0;
}