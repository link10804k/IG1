#include "Scene4.h"

#include "Ground.h"
#include "Texture.h"
#include "Star3D.h"
#include "Box.h"
#include "GlassParapet.h"
#include "Photo.h"

#include "TextureManager.h"

#include "glm/gtc/matrix_transform.hpp"

void Scene4::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Suelo
	Ground* g = new Ground(400, 400, 4, 4);
	
	Texture* groundText = new Texture();
	groundText->load("../assets/images/baldosaC.png", 255); // ASK: Método para asignarle la textura?
	
	g->setTexture(groundText);
	
	gObjects.push_back(g); 

	// Cubo
	Box* box = new Box(75);
	box->setTexture(TEXTURE_MANAGER->getTexture("papelE.png"), TEXTURE_MANAGER->getTexture("container.jpg"));

	box->setModelMat(glm::translate(box->modelMat(), glm::vec3(100, 37.5, -100)));

	gObjects.push_back(box);

	// Estrella
	Star3D* star = new Star3D(10, 8, 20);
	star->setTexture(TEXTURE_MANAGER->getTexture("rueda.png"));

	star->setModelMat(glm::translate(star->modelMat(), glm::vec3(100, 37.5, -100)));
	
	gObjects.push_back(star);

	// Ventana
	//GlassParapet* window = new GlassParapet();
	//
	//Texture* windowText = new Texture();
	//windowText->load("../assets/images/windowC.png", 155); 
	//
	//window->setTexture(windowText);
	//
	//gTranslucidObjects.push_back(window);

	// Foto
	Photo* ph = new Photo(100, 100);

	ph->setModelMat(glm::translate(ph->modelMat(), glm::vec3(0, 0, -5)));

	gObjects.push_back(ph);
}