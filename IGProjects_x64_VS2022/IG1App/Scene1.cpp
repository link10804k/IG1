#include "Scene1.h"

#include "RegularPolygon.h"
#include "RGBTriangle.h"

void Scene1::init() {
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	glm::vec4 magenta = { 1,0,1,1 };
	glm::vec4 amarillo = { 1,1,0,1 };

	gObjects.push_back(new RegularPolygon(6, 100, magenta));
	gObjects.push_back(new RegularPolygon(60, 100, amarillo));
}
