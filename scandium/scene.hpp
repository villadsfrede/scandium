#ifndef SCAN_SCENE_H
#define SCAN_SCENE_H

#include "scan.h"
#include "shape.hpp"

class Scene {
public:
	Scene(std::shared_ptr<Shape> Shape) {Shapes.push_back(Shape);}

	std::vector<std::shared_ptr<Shape>> Shapes;
};

#endif
