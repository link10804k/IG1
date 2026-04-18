#include "Scene5.h"

#include "Torus.h"

void Scene5::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Toro
	Torus* t = new Torus(200, 50);
	t->setColor({0.0f,1.0f,0.0f,1.0f});
	gObjects.push_back(t);
}
