#include "Scene8.h"

#include "Sphere.h"
#include "Droid.h"
#include "CompoundEntity.h"

#include "glm/gtc/matrix_transform.hpp"

void Scene8::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	int planetRadius = 200;
    // Planeta
    Sphere* planeta = new Sphere(planetRadius, 50, 50);
	planeta->setColor({ 171 / 255.0, 33 / 255.0, 72 / 255.0, 0 });
	gObjects.push_back(planeta);

	// Nodo ficticio 	
	CompoundEntity* ghost = new CompoundEntity();
	gObjects.push_back(ghost);

	this->ghost = ghost;

    // Androide
	int droidRadius = 20;
	Droid* d = new Droid(20);
	d->setModelMat(glm::translate(d->modelMat(), glm::vec3(0, planetRadius + droidRadius, 0)));
	ghost->addEntity(d);

	droid = d;
}

void Scene8::rotate() {
	float angle = 5.0f;
	ghost->setModelMat(glm::rotate(ghost->modelMat(), glm::radians(angle), glm::vec3(0, 1, 0)));
}

void Scene8::orbit(){
	float angle = 5.0f;
	ghost->setModelMat(glm::rotate(ghost->modelMat(), glm::radians(angle), glm::vec3(1, 0, 0)));

	droid->walk();
}