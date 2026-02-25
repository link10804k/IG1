#include "Scene4.h"

#include "Ground.h"
#include "Texture.h"
#include "BoxOutline.h"

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
	gObjects.push_back(new BoxOutline(100));
}