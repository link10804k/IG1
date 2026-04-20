#include "ColorMaterialEntity.h"

#include "IG1App.h"

ColorMaterialEntity::ColorMaterialEntity() {
	mShader = Shader::get("simple_light");
	normalShader = Shader::get("normals");
}

void ColorMaterialEntity::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		mShader->use();
		glm::mat4 viewMat = IG1App::s_ig1app.camera().viewMat();
		mShader->setUniform("lightDir", viewMat * glm::normalize(glm::vec4(-1, -1.5, -1.25, 0)));
		SingleColorEntity::render(modelViewMat);

		if (mShowNormals) {
			normalShader->use();
			mMesh->render();
		}
	}
}
