#include "EntityWithMaterial.h"

EntityWithMaterial::EntityWithMaterial() {
	mShader = Shader::get("light");
	normalShader = Shader::get("normals");
}

void EntityWithMaterial::render(const glm::mat4& modelViewMat) const
{
	if (mMesh != nullptr) {
		mShader->use();
		// Carga los atributos del material en la GPU
		mMaterial.upload(*mShader);
		upload(modelViewMat * mModelMat);
		mMesh->render();
	}

	if (mMesh != nullptr) {
		if (mShowNormals) {
			normalShader->use();
			normalShader->setUniform("modelView", modelViewMat * mModelMat);
			mMesh->render();
		}
	}
}