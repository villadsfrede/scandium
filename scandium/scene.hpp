#ifndef SCAN_SCENE_H
#define SCAN_SCENE_H

#include "scan.h"
#include "shape.hpp"
#include "light.hpp"

class Scene {
public:
	// Scene data
	std::vector<std::shared_ptr<Shape>> Shapes;
	std::shared_ptr<DistantLight> Lights;

	Scene() {}

	// Funktioner til at tilføje objekter og lys
	void addShape(std::shared_ptr<Shape> Shape) { Shapes.push_back(Shape); }
	void addSLight(std::shared_ptr<DistantLight> Light) { Lights = Light; }
};

#endif
