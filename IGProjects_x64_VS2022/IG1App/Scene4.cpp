#include "Scene4.h"

#include "Ground.h"

void Scene4::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Suelo
	gObjects.push_back(new Ground(100, 100));
}