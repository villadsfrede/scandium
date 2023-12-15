#include <iostream>
#include "math.hpp"
#include "vector.hpp"
#include "ray.hpp"
#include "transform.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "cylinder.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "scene.hpp"

int main() {
	SquareMatrix<4> sphereMAT = SquareMatrix<4>();
	SquareMatrix<4> isphereMAT = SquareMatrix<4>();
	sphereMAT.m[2][3] = -5;
	isphereMAT.m[2][3] = 5;
	Transform sphereTRA = Transform(sphereMAT);
	Transform isphereTRA = Transform(isphereMAT);
	auto sphere = std::make_shared<Sphere>(&sphereTRA, &isphereTRA, 1, 1);

	SquareMatrix<4> sphereMAT2 = SquareMatrix<4>();
	SquareMatrix<4> isphereMAT2 = SquareMatrix<4>();
	sphereMAT2.m[2][3] = -5;
	isphereMAT2.m[2][3] = 5;
	sphereMAT2.m[0][3] = -3;
	isphereMAT2.m[0][3] = 3;
	Transform sphereTRA2 = Transform(sphereMAT2);
	Transform isphereTRA2 = Transform(isphereMAT2);
	auto sphere2 = std::make_shared<Sphere>(&sphereTRA2, &isphereTRA2, 0, 1);

	SquareMatrix<4> bigsphereMAT = SquareMatrix<4>();
	SquareMatrix<4> ibigsphereMAT = SquareMatrix<4>();
	bigsphereMAT.m[2][3] = -5;
	ibigsphereMAT.m[2][3] = 5;
	bigsphereMAT.m[1][3] = -10;
	ibigsphereMAT.m[1][3] = 10;
	Transform bigsphereTRA = Transform(bigsphereMAT);
	Transform ibigsphereTRA = Transform(ibigsphereMAT);
	auto bigsphere = std::make_shared<Sphere>(&bigsphereTRA, &ibigsphereTRA, 0, 8);

	SquareMatrix<4> lightMAT = SquareMatrix<4>();
	Transform lightTRA = Transform(lightMAT);
	auto light = std::make_shared<DistantLight>(&lightTRA, Vector3f(1, 1, 1), 1500, Vector3f(0, 0, -1));

	Scene scene = Scene();

	scene.addShape(sphere);
	scene.addShape(sphere2);
	scene.addShape(bigsphere);
	scene.addSLight(light);

	SquareMatrix<4> cameraMAT = SquareMatrix<4>();
	Transform cameraTRA = Transform(cameraMAT);
	ProjectiveCamera camera = ProjectiveCamera(&cameraTRA, scene, 1000, 1000, 1.5);

	camera.Render();
	

	/*
	SquareMatrix<4> m = SquareMatrix<4>();
	m.m[0][3] = 5;
	m.m[2][3] = -10;

	SquareMatrix<4> mi = Inverse(m);
	std::cout << mi.m[0][3] << std::endl;
	std::cout << mi.m[2][3] << std::endl;
	*/

	return 0;
}