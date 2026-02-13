#include "RGBRectangle.h"

RGBRectangle::RGBRectangle(GLdouble w, GLdouble h) {
	mMesh = Mesh::generateRGBRectangle(w, h);
}

void RGBRectangle::render(glm::mat4 const& modelViewMat) const {
	
	// Cambiamos el modo de dibujado para toda la figura porque no están disponibles el FRONT ni el BACK para glPolygonMode
	glEnable(GL_CULL_FACE);
	// Dibujamos la cara frontal con líneas
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	EntityWithColors::render(modelViewMat);
	// Dibujamos la cara trasera con fill
	glCullFace(GL_FRONT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	EntityWithColors::render(modelViewMat);

	glDisable(GL_CULL_FACE);
}