#include "Scene6.h"

#include "SphereWithTexture.h"
#include "IndexedBox.h"
#include "TextureManager.h"

void Scene6::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Cubo
	IndexedBox* box = new IndexedBox(200);
	box->setColor(glm::vec4(0,1,0,1));
	gObjects.push_back(box);
}