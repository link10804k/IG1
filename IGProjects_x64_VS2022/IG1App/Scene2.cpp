#include "Scene2.h"

#include "RegularPolygon.h"
#include "RGBTriangle.h"
#include "RGBRectangle.h"

void Scene2::init() {
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	GLdouble r = 100;

	gObjects.push_back(new RGBRectangle(100, 100));
	gObjects.push_back(new RGBTriangle(33, r, 0));

	glm::vec4 magenta = { 1,0,1,1 };

	gObjects.push_back(new RegularPolygon(60, r, magenta));
}