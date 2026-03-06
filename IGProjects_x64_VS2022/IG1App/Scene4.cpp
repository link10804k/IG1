#include "Scene4.h"

#include "Ground.h"
#include "Texture.h"
#include "BoxOutline.h"
#include "Star3D.h"
#include "GlassParapet.h"

#include "TextureManager.h"

#include "glm/gtc/matrix_transform.hpp"

void Scene4::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Suelo
	//Ground* g = new Ground(100, 100, 4, 4);
	//
	//Texture* groundText = new Texture();
	//groundText->load("../assets/images/baldosaC.png", 255); // ASK: Método para asignarle la textura?
	//
	//g->setTexture(groundText);
	//
	//gObjects.push_back(g); 

	// Cubo
	//BoxOutline* box = new BoxOutline(100);
	//box->setTexture(TEXTURE_MANAGER->getTexture("papelE.png"), TEXTURE_MANAGER->getTexture("container.jpg"));
	//gObjects.push_back(box);

	// Estrella
	//Star3D* star = new Star3D(100, 8, 100);
	//
	//Texture* starText = new Texture();
	//starText->load("../assets/images/rueda.png", 255);
	//
	//star->setTexture(starText);
	//
	//gObjects.push_back(star);

	// Ventana
	GlassParapet* window = new GlassParapet();
	
	Texture* windowText = new Texture();
	windowText->load("../assets/images/windowC.png", 155); 
	
	window->setTexture(windowText);

	//window->setModelMat(glm::translate(window->modelMat(), glm::vec3(100, 100, 100)));
	
	gTranslucidObjects.push_back(window);
}