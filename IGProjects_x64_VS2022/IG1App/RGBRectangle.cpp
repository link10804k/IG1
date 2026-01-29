#include "RGBRectangle.h"

RGBRectangle::RGBRectangle(GLdouble w, GLdouble h) {
	mMesh = Mesh::generateRGBRectangle(w, h);
}

void RGBRectangle::render(glm::mat4 const& modelViewMat) const {
	glm::vec3 zAxis;
	glm::vec3 zModel;
	for (int i = 0; i < 3; ++i) {
		zAxis[i] = modelViewMat[2][i];
		zModel[i] = mModelMat[2][i];
	}
	
	// Cambiamos el modo de dibujado para toda la figura porque no están disponibles el FRONT ni el BACK para glPolygonMode
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	EntityWithColors::render(modelViewMat);
	glCullFace(GL_FRONT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	EntityWithColors::render(modelViewMat);

	glDisable(GL_CULL_FACE);
}