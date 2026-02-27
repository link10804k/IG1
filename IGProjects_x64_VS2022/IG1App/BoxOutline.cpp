#include "BoxOutline.h"

BoxOutline::BoxOutline(GLdouble length) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}

void BoxOutline::setTexture(Texture* externTexture, Texture* innerTexture) {
	mTexture = externTexture;
	_innerTexture = innerTexture;
}

void BoxOutline::render(const glm::mat4& modelViewMat) const {
	glEnable(GL_CULL_FACE);
	// Dibujamos la cara frontal con la textura frontal
	glCullFace(GL_BACK);
	renderFace(modelViewMat, mTexture);

	// Dibujamos la cara trasera con la textura trasera
	glCullFace(GL_FRONT);
	renderFace(modelViewMat, _innerTexture);

	glDisable(GL_CULL_FACE);
}
void BoxOutline::renderFace(const glm::mat4& modelViewMat, Texture* texture) const {
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		mShader->use();
		mShader->setUniform("modulate", mModulate); // Fijamos el uniform modulate con mModulate

		if (texture != nullptr) texture->bind(); // Le decimos a la GPU que utilice esta textura

		upload(aMat);
		mMesh->render();

		if (texture != nullptr) texture->unbind(); // Le decimos a la GPU que ya no la tiene que utilizar
	}
}