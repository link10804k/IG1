#include "Cube.h"

Cube::Cube(GLdouble lenght) {
	mMesh = Mesh::generateCube(lenght);
}

void Cube::render(glm::mat4 const& modelViewMat) const {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	SingleColorEntity::render(modelViewMat);
	glCullFace(GL_FRONT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	SingleColorEntity::render(modelViewMat);

	glDisable(GL_CULL_FACE);
}