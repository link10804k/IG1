#include "Star3D.h"

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h) {
	mMesh = Mesh::generateStar3D(re, np, h);

	mColor = glm::vec4(0, 0, 0, 1);
}

void Star3D::render(const glm::mat4& modelViewMat) const {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	SingleColorEntity::render(modelViewMat);
}