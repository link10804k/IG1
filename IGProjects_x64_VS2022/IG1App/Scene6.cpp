#include "Scene6.h"

#include "IndexedBox.h"

void Scene6::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Cubo
	IndexedBox* ib = new IndexedBox(100);
	ib->setColor({ 0, 1, 0, 1 });
	gObjects.push_back(ib);
}