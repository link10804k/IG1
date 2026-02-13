#include "RGBTriangle.h"

#include "glm/gtc/matrix_transform.hpp"

#include "Debug.h"

RGBTriangle::RGBTriangle(GLuint r) {
	mMesh = Mesh::generateTriangleWithColors(r);
}

// Rota el triángulo sobre si mismo y sobre el orígen de coordenadas
void RGBTriangle::update() {
	GLfloat ang = glm::radians(15.0f); // En grados
	mModelMat = glm::rotate(glm::mat4(1), ang, glm::vec3(0, 0, 1))*glm::rotate(mModelMat, -2*ang, glm::vec3(0, 0, 1));
}