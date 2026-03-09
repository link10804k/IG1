#include "EntityWithTexture.h"

EntityWithTexture::EntityWithTexture() {
	mShader = Shader::get("texture");
}

void EntityWithTexture::setTexture(Texture* texture) {
	mTexture = texture;
}

void EntityWithTexture::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		mShader->use();
		mShader->setUniform("modulate", mModulate); // Fijamos el uniform modulate con mModulate

		if (mTexture != nullptr) mTexture->bind(); // Le decimos a la GPU que utilice esta textura

		upload(aMat);
		mMesh->render();

		if (mTexture != nullptr) mTexture->unbind(); // Le decimos a la GPU que ya no la tiene que utilizar
	}
}


