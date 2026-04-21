#include "Scene6.h"

#include "SphereWithTexture.h"
#include "TextureManager.h"

void Scene6::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Esfera con textura
	SphereWithTexture* st = new SphereWithTexture(200, 40, 40);
	st->setTexture(TEXTURE_MANAGER->getTexture("container.jpg"));
	gObjects.push_back(st);
}