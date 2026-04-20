#include "Scene9.h"
#include "Sphere.h"
#include "Cone.h"
#include "Disk.h"
#include "CompoundEntity.h"

#include "glm/gtc/matrix_transform.hpp"

void Scene9::init() {
	Scene::init();

	CompoundEntity* snowMan = new CompoundEntity();
	gObjects.push_back(snowMan);

	int snowManRadius = 100;
	int snowManHeadRadius = snowManRadius * 0.7;

	// Cuerpo
	Sphere* cuerpo = new Sphere(snowManRadius, 50, 50);
	cuerpo->setColor({243.0/255, 243.0/255, 243.0/255, 1});
	snowMan->addEntity(cuerpo);

	// Cabeza
	CompoundEntity* cabeza = new CompoundEntity();
	cabeza->setModelMat(glm::translate(cabeza->modelMat(), glm::vec3(0, snowManHeadRadius + snowManRadius, 0)));
	snowMan->addEntity(cabeza);

	Sphere* cabezaSphere = new Sphere(snowManHeadRadius,50,50);
	cabezaSphere->setColor({243.0/255, 243.0/255, 243.0/255, 1});
	cabeza->addEntity(cabezaSphere);

	//Nariz
	float alturaNariz = snowManHeadRadius / 3;
	Cone* nariz = new Cone(alturaNariz, snowManHeadRadius / 10, 0, 50, 50);
	nariz->setModelMat(glm::translate(nariz->modelMat(), glm::vec3(0, -snowManHeadRadius / 6, snowManHeadRadius + alturaNariz / 2)));
	nariz->setModelMat(glm::rotate(nariz->modelMat(), glm::radians(90.0f), glm::vec3(1, 0, 0)));
	nariz->setColor({1, 0.4, 0, 1});
	cabeza->addEntity(nariz);

	//Ojos
	float alturaOjos = snowManHeadRadius / 4;
	Cone* ojoIzq = new Cone(alturaOjos, snowManHeadRadius / 5, 0, 50, 50);
	ojoIzq->setModelMat(glm::translate(ojoIzq->modelMat(), glm::vec3(snowManHeadRadius / 3, alturaOjos, snowManHeadRadius + alturaOjos / 2)));
	ojoIzq->setModelMat(glm::rotate(ojoIzq->modelMat(), glm::radians(90.0f), glm::vec3(1, 0, 0)));
	ojoIzq->setColor({ 0, 0.5, 0.5, 1 });
	cabeza->addEntity(ojoIzq);

	Cone* ojoDer = new Cone(alturaOjos, snowManHeadRadius / 5, 0, 50, 50);
	ojoDer->setModelMat(glm::translate(ojoDer->modelMat(), glm::vec3(-snowManHeadRadius / 3, alturaOjos, snowManHeadRadius + alturaOjos / 2)));
	ojoDer->setModelMat(glm::rotate(ojoDer->modelMat(), glm::radians(90.0f), glm::vec3(1, 0, 0)));
	ojoDer->setColor({ 0, 0.5, 0.5, 1 });
	cabeza->addEntity(ojoDer);
	

	//Sombrero
	GLdouble alturaGorro = snowManHeadRadius / 2 ;
	CompoundEntity* sombrero = new CompoundEntity();
	sombrero->setModelMat(glm::translate(sombrero->modelMat(), glm::vec3(0, snowManHeadRadius / 2 + alturaGorro / 2, 0)));
	cabeza->addEntity(sombrero);

	Cone* gorro = new Cone(alturaGorro, snowManHeadRadius, snowManHeadRadius, 50, 50);
	gorro->setColor({0, 0, 1, 1});
	sombrero->addEntity(gorro);

	Disk* visera = new Disk(snowManHeadRadius * 1.4, 0, 30, 30);
	visera->setModelMat(glm::translate(visera->modelMat(), glm::vec3(0, -alturaGorro / 2, 0)));
	visera->setColor({ 0, 1, 1, 1 });
	sombrero->addEntity(visera);

	Disk* tapaGorro = new Disk(snowManHeadRadius, 0, 30, 30);
	tapaGorro->setModelMat(glm::translate(tapaGorro->modelMat(), glm::vec3(0, alturaGorro / 2, 0)));
	tapaGorro->setColor({ 1, 0, 0, 1 });
	sombrero->addEntity(tapaGorro);
}