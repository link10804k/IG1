#include "Scene2.h"

#include "RegularPolygon.h"
#include "RGBTriangle.h"
#include "RGBRectangle.h"

#include "glm/gtc/matrix_transform.hpp"

void Scene2::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Radio de la circunferencia 
	GLdouble r = 100;
	// Tamaño del cuadrado
	GLdouble length = glm::sin(glm::radians(45.0f)) * r * 2;

	// Rectángulo RGB
	gObjects.push_back(new RGBRectangle(length, length));
	// Triángulo RGB
	RGBTriangle* t = new RGBTriangle(33);
	// Desplazamiento triángulo hacia la circunferencia
	t->setModelMat(glm::translate(t->modelMat(), glm::vec3(r, 0, 0)));
	gObjects.push_back(t);

	glm::vec4 magenta = { 1,0,1,1 };
	// Circunferencia magenta
	gObjects.push_back(new RegularPolygon(60, r, magenta));
}