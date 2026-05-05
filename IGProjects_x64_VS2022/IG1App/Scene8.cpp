#include "Scene8.h"

#include "Sphere.h"
#include "Droid.h"
#include "CompoundEntity.h"
#include "Light.h"

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
	Droid* d = new Droid(droidRadius);
	d->setModelMat(glm::translate(d->modelMat(), glm::vec3(0, planetRadius + droidRadius, 0)));
	ghost->addEntity(d);

	droid = d;

	// Luz posicional
	posLight = new PosLight();
	posLight->setEnabled(true);

	posLight->setAmb({ 0.25, 0.25, 0.25 });
	posLight->setDiff({ 0.6, 0.6, 0.6 });
	posLight->setSpec({ 0, 0.2, 0 });

	posLight->setPosition(glm::vec3(500, 500, 0));

	gLights.push_back(posLight);

	// Luz foco
	spotLight = new SpotLight();
	spotLight->setEnabled(true);

	spotLight->setAmb({ 0.25, 0.25, 0.25 });
	spotLight->setDiff({ 0.6, 0.6, 0.6 });
	spotLight->setSpec({ 0, 0.2, 0 });

	glm::vec3 position = { 0, 500, 500 };
	spotLight->setPosition(glm::vec3(position));
	spotLight->setDirection(glm::normalize(glm::vec3(0, 0, 0) - position));
	spotLight->setCutoff(5.0f, 15.0f);

	gLights.push_back(spotLight);

	// Luz androide
	droidLight = droid->getDroidLight();
	gLights.push_back(droidLight);
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

void Scene8::setBackgroundColor(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

bool Scene8::handleInput(char c) {
	switch (c) {
	case 'f':
		rotate();
		return true;
	case 'g':
		orbit();
		return true;
	case 't':
		posLight->setEnabled(!posLight->enabled());
		return true;
	case 'y':
		spotLight->setEnabled(!spotLight->enabled());
		return true;
	case 'h':
		droidLight->setEnabled(!droidLight->enabled());
		return true;
	default:
		return Scene::handleInput(c);
	}
	
}

