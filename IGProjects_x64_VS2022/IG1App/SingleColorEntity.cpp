#include "SingleColorEntity.h"

SingleColorEntity::SingleColorEntity(glm::vec4 mColor) : mColor(mColor) {
	mShader = Shader::get("simple");
}

void SingleColorEntity::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		mShader->use();
		mShader->setUniform("color", mColor);

		upload(aMat);
		mMesh->render();
	}
}

glm::vec4 SingleColorEntity::getColor() {
	return mColor;
}
void SingleColorEntity::setColor(glm::vec4 mColor) {
	this->mColor = mColor;
}
