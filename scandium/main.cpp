#include <iostream>
#include "math.hpp"
#include "vector.hpp"
#include "ray.hpp"
#include "transform.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "trianglemesh.hpp"
#include "image.hpp"
#include "camera.hpp"
#include "scene.hpp"

int main() {
	// Første kugle
	SquareMatrix<4> sphereMAT = SquareMatrix<4>();
	SquareMatrix<4> isphereMAT = SquareMatrix<4>();
	sphereMAT.m[2][3] = -5;
	isphereMAT.m[2][3] = 5;
	Transform sphereTRA = Transform(sphereMAT);
	Transform isphereTRA = Transform(isphereMAT);
	auto sphere = std::make_shared<Sphere>(&sphereTRA, &isphereTRA, 2, 1);
	
	// Anden kugle
	SquareMatrix<4> sphereMAT2 = SquareMatrix<4>();
	SquareMatrix<4> isphereMAT2 = SquareMatrix<4>();
	sphereMAT2.m[2][3] = -5;
	isphereMAT2.m[2][3] = 5;
	sphereMAT2.m[0][3] = -3;
	isphereMAT2.m[0][3] = 3;
	Transform sphereTRA2 = Transform(sphereMAT2);
	Transform isphereTRA2 = Transform(isphereMAT2);
	auto sphere2 = std::make_shared<Sphere>(&sphereTRA2, &isphereTRA2, 1, 1);

	// Tredje og største kugle
	SquareMatrix<4> bigsphereMAT = SquareMatrix<4>();
	SquareMatrix<4> ibigsphereMAT = SquareMatrix<4>();
	bigsphereMAT.m[2][3] = -5;
	ibigsphereMAT.m[2][3] = 5;
	bigsphereMAT.m[1][3] = -10;
	ibigsphereMAT.m[1][3] = 10;
	Transform bigsphereTRA = Transform(bigsphereMAT);
	Transform ibigsphereTRA = Transform(ibigsphereMAT);
	auto bigsphere = std::make_shared<Sphere>(&bigsphereTRA, &ibigsphereTRA, 0, 8);
	
	// Trekant information
	std::vector<Vector3f> verts = { Vector3f(-1,0,0), Vector3f(0,0,0), Vector3f(0,1,0)};
	std::vector<int> vertsIn = { 0,1,2 };

	// Trekant objekt
	SquareMatrix<4> trigMat = SquareMatrix<4>();
	SquareMatrix<4> itrigMat = SquareMatrix<4>();
	// x
	//trigMat.m[0][3] = 0;
	//itrigMat.m[0][3] = 0;
	// y
	//trigMat.m[1][3] = 0;
	//itrigMat.m[1][3] = 0;
	// z
	trigMat.m[2][3] = -10;
	itrigMat.m[2][3] = 10;
	Transform trigTRA = Transform(trigMat);
	Transform itrigTRA = Transform(itrigMat);
	auto trig = std::make_shared<TriangleMesh>(&trigTRA, &itrigTRA, 0, &verts, &vertsIn);

	// Lys objekt
	SquareMatrix<4> lightMAT = SquareMatrix<4>();
	Transform lightTRA = Transform(lightMAT);
	auto light = std::make_shared<DistantLight>(&lightTRA, Vector3f(1, 1, 1), 1500, Vector3f(0, 0, -1));

	Scene scene = Scene();

	// Tilføjelse af objekter til scene
	//scene.addShape(sphere);
	//scene.addShape(sphere2);
	//scene.addShape(bigsphere);
	scene.addShape(trig);
	scene.addSLight(light);

	// Kamera objekt
	SquareMatrix<4> cameraMAT = SquareMatrix<4>();
	Transform cameraTRA = Transform(cameraMAT);
	ProjectiveCamera camera = ProjectiveCamera(&cameraTRA, scene, 1000, 1000, 1.1);

	camera.Render();

	return 0;
}