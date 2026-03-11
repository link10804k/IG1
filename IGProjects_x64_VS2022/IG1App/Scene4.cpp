#include "Scene4.h"

#include "Ground.h"
#include "Texture.h"
#include "Star3D.h"
#include "Box.h"
#include "GlassParapet.h"
#include "Grass.h"
#include "Photo.h"

#include "TextureManager.h"

#include "glm/gtc/matrix_transform.hpp"

void Scene4::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Suelo
	Ground* g = new Ground(400, 400, 4, 4);
	
	g->setTexture(TEXTURE_MANAGER->getTexture("baldosaC.png"));
	
	gObjects.push_back(g); 

	// Cubo
	Box* box = new Box(75);
	box->setTexture(TEXTURE_MANAGER->getTexture("papelE.png"), TEXTURE_MANAGER->getTexture("container.jpg"));

	box->setModelMat(glm::translate(box->modelMat(), glm::vec3(100, 38.5, -100)));

	gObjects.push_back(box);

	// Estrella
	Star3D* star = new Star3D(10, 8, 20);
	star->setTexture(TEXTURE_MANAGER->getTexture("rueda.png"));

	star->setModelMat(glm::translate(star->modelMat(), glm::vec3(100, 37.5, -100)));
	
	gObjects.push_back(star);

	// Ventana
	GlassParapet* window = new GlassParapet(100);
	
	window->setTexture(TEXTURE_MANAGER->getTexture("windowC.png", 155));

	window->setModelMat(glm::scale(window->modelMat(), glm::vec3(4, 1, 4)));
	
	gTranslucidObjects.push_back(window);

	// Grass
	Grass* grass = new Grass(50, 50);

	grass->setTexture(TEXTURE_MANAGER->getTexture("grass.png"));

	grass->setModelMat(glm::translate(grass->modelMat(), glm::vec3(50, 25, 125)));

	gObjects.push_back(grass);

	// Foto
	Photo* ph = new Photo(100, 100);

	// La movemos un poco hacia arriba para que no haya overlap con el suelo (aquí el eje z es el vertical porque es un rectángulo rotado)
	ph->setModelMat(glm::translate(ph->modelMat(), glm::vec3(0, 0, -1)));

	gObjects.push_back(ph);
}