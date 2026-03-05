#include "GlassParapet.h"

GlassParapet::GlassParapet() {
	mMesh = Mesh::generateBoxOutlineTexCor(100);
}

void GlassParapet::render(const glm::mat4& modelViewMat) const {
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// TODO: Funciona raro (se ve lo de atrás por delante)
	EntityWithTexture::render(modelViewMat);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}
