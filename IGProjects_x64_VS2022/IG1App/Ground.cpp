#include "Ground.h"

#include "glm/gtc/matrix_transform.hpp"

Ground::Ground(GLdouble w, GLdouble d) {
	mMesh = Mesh::generateRGBRectangle(w, d);
	float ang = glm::radians(90.0f);

	mModelMat = glm::rotate(glm::mat4(1), -ang, glm::vec3(0, 1, 0)) * glm::rotate(glm::mat4(1), ang, glm::vec3(1, 0, 0)) * mModelMat;
}

void Ground::render(glm::mat4 const& modelViewMat) const {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	EntityWithColors::render(modelViewMat);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}