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
	mModelMat = glm::rotate(glm::mat4(1), ang, glm::vec3(0, 0, 1))*glm::rotate(mModelMat, -2*ang, glm::vec3(0, 0, 1));
}