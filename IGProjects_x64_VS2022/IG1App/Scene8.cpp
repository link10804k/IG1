#include "Scene8.h"

#include "Sphere.h"
#include "Sphere.h"
#include "Droid.h"

#include "glm/gtc/matrix_transform.hpp"

void Scene8::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	int planetRadius = 200;
    // Planeta
    //FIXME: wtf la luz está verde ¿?¿?¿
    Sphere* planeta = new Sphere(planetRadius, 50, 50);
	planeta->setColor({ 171 / 255.0, 33 / 255.0, 72 / 255.0, 0 });
	gObjects.push_back(planeta);

    // Androide
	int droidRadius = 20;
	Droid* d = new Droid(20);
	d->setModelMat(glm::translate(d->modelMat(), glm::vec3(0, planetRadius + droidRadius, 0)));
	gObjects.push_back(d);
}