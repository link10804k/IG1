#include "Scene1.h"

#include "RegularPolygon.h"

void Scene1::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	glm::vec4 magenta = { 1,0,1,1 };
	glm::vec4 amarillo = { 1,1,0,1 };

	// Hexágono magenta
	gObjects.push_back(new RegularPolygon(6, 100, magenta));
	// Circunferencia amarilla
	gObjects.push_back(new RegularPolygon(60, 100, amarillo));
}
