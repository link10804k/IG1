#include "Scene5.h"

#include "Torus.h"

void Scene5::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Suelo
	Torus* t = new Torus(200, 50);

	gObjects.push_back(t);
}
