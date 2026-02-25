#include "BoxOutline.h"

BoxOutline::BoxOutline(GLdouble length) {
	mMesh = Mesh::generateBoxOutline(length);

	mColor = glm::vec4(0, 0, 0, 1);
}

void BoxOutline::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		SingleColorEntity::render(modelViewMat);
	}
}