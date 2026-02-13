#include "Scene3.h"

#include "RGBCube.h"

#include "glm/gtc/matrix_transform.hpp"

void Scene3::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Cubo
	GLdouble length = 100;
	RGBCube* c = new RGBCube(length);
	c->setModelMat(glm::translate(c->modelMat(), glm::vec3(length / 2, length / 2, -length / 2)));
	gObjects.push_back(c);
}
