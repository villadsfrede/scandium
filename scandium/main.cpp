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

int main() {
	float sm[4][4] = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };

	float st1[4][4] = { {1,0,0,2}, {0,1,0,0}, {0,0,1,-5}, {0,0,0,1} };
	float ist1[4][4] = { {1,0,0,-2}, {0,1,0,}, {0,0,1,5}, {0,0,0,1} };

	Transform tst1 = Transform(st1);
	Transform tist1 = Transform(ist1);

	auto s1 = std::make_shared<Sphere>(&tst1, &tist1, 1);

	float st2[4][4] = { {1,0,0,-2}, {0,1,0,0}, {0,0,1,-5}, {0,0,0,1} };
	float ist2[4][4] = { {1,0,0,2}, {0,1,0,}, {0,0,1,5}, {0,0,0,1} };

	Transform tst2 = Transform(st2);
	Transform tist2 = Transform(ist2);

	auto s2 = std::make_shared<Sphere>(&tst2, &tist2, 1);

	float lt[4][4] = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
	Transform tlt = Transform(lt);

	auto l = std::make_shared<DistantLight>(&tlt, Vector3f(1, 1, 1), 2500, Vector3f(0, 0, -1));

	Scene scene = Scene();

	scene.addShape(s1);
	scene.addShape(s2);
	scene.addSLight(l);

	Transform t = Transform(sm);

	ProjectiveCamera c = ProjectiveCamera(&t, scene, 1000, 1000, 1.5);
	
	c.Render();

	return 0;
}