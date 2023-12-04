#include <iostream>
#include "math.hpp"
#include "vector.hpp"
#include "ray.hpp"
#include "transform.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "scene.hpp"

float sm[4][4] = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };

float st[4][4] = { {1,0,0,0}, {0,1,0,0}, {0,0,1,-10}, {0,0,0,1} };
float ist[4][4] = { {1,0,0,0}, {0,1,0,}, {0,0,1,10}, {0,0,0,1} };

Transform tst = Transform(st);
Transform tist = Transform(ist);

auto s = std::make_shared<Sphere>(&tst, &tist, 1);

Scene scn = Scene(s);

Transform t = Transform(sm);

ProjectiveCamera c = ProjectiveCamera(&t, scn, 1000, 1000, 1.57);


int main() {
	c.Render();

	return 0;
}