#include "RGBTriangle.h"
#include "RegularPolygon.h"

#include "glm/gtc/matrix_transform.hpp"

RGBTriangle::RGBTriangle(GLuint r, GLdouble x, GLdouble y) {
	mMesh = Mesh::generateTriangleWithColors(r, x, y);
}

void RGBTriangle::update() {
	GLfloat ang = 15; // En grados

	GLdouble x = mModelMat[0][3];
	GLdouble y = mModelMat[1][3];

	//mModelMat = glm::rotate(mModelMat, glm::radians(-ang), glm::vec3(0.0f, 0.0f, 1.0f));

	mModelMat[0][3] = 0;
	mModelMat[1][3] = 0;

	//mModelMat = glm::rotate(mModelMat, glm::radians(ang), glm::vec3(0.0f, 0.0f, 1.0f));
}