#include "RGBTriangle.h"
#include "RegularPolygon.h"

#include "glm/gtc/matrix_transform.hpp"

#include "Debug.h"

RGBTriangle::RGBTriangle(GLuint r, GLdouble x, GLdouble y) {
	mMesh = Mesh::generateTriangleWithColors(r);

	mModelMat = glm::translate(mModelMat, glm::vec3(x, y, 0));
}

void RGBTriangle::update() {
	GLfloat ang = glm::radians(15.0f); // En grados

	GLfloat x = mModelMat[3][0];
	GLfloat y = mModelMat[3][1];
	GLfloat h = glm::sqrt(glm::pow(x, 2) + glm::pow(y, 2)); // Calculamos la distancia al 0,0

	mModelMat = glm::rotate(mModelMat, totalAngle * 2, glm::vec3(0, 0, 1)); // Orientamos el triángulo al 0,0
	mModelMat = glm::translate(mModelMat, glm::vec3(-h, 0, 0)); // Lo llevamos allí

	mModelMat = glm::rotate(mModelMat, ang, glm::vec3(0,0,1)); // Lo rotamos 15 grados
	totalAngle += ang; // Almacenamos el ángulo total rotado

	mModelMat = glm::translate(mModelMat, glm::vec3(h, 0, 0)); // Lo devolvemos a su posición correspondiente de la circunferencia por la que orbita
	
	mModelMat = glm::rotate(mModelMat, -totalAngle * 2, glm::vec3(0, 0, 1)); // Rotamos el doble del ángulo total hacia la dirección contraria 
																			// para que quede como si estuviera rotando sobre si mismo en sentido horario
}