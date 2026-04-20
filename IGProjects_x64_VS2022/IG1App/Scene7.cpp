#include "Scene7.h"

#include "Droid.h"


void Scene7::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Androide
	Droid* d = new Droid(200);
	gObjects.push_back(d);
}