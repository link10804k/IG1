#include "Scene0.h"

#include "Sphere.h"

#include "glm/gtc/matrix_transform.hpp"

void Scene0::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Esfera amarilla
	Sphere* yellowSphere = new Sphere(100, 50, 50);
	Material yellow(glm::vec3(1, 1, 0));
	yellowSphere->setMaterial(yellow);
	yellowSphere->setModelMat(glm::translate(yellowSphere->modelMat(), glm::vec3(400, 0, 0)));

	gObjects.push_back(yellowSphere);

	// Esfera dorada
	Sphere* goldenSphere = new Sphere(100, 50, 50);
	Material golden;
	golden.setGold();
	goldenSphere->setMaterial(golden);
	goldenSphere->setModelMat(glm::translate(goldenSphere->modelMat(), glm::vec3(0, 0, 400)));

	gObjects.push_back(goldenSphere);
}