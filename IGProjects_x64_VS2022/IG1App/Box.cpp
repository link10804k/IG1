#include "Box.h"

#include "glm/gtc/matrix_transform.hpp"

Box::Box(GLdouble length) : BoxOutline(length) {
	assert(mMesh != nullptr);

	mMeshTop = Mesh::generateRectangleTexCor(length, length, 1, 1);
	mMeshBot = Mesh::generateRectangleTexCor(length, length, 1, 1);

	mModelMatTop = glm::translate(mModelMatTop, glm::vec3(0, length / 2, 0));
	mModelMatBot = glm::translate(mModelMatBot, glm::vec3(0, -length / 2, 0));
}

void Box::render(const glm::mat4& modelViewMat) const {
	BoxOutline::render(modelViewMat);

	//glEnable(GL_CULL_FACE);
	//// Dibujamos la cara frontal con la textura frontal
	//glCullFace(GL_BACK);
	//renderFace(mMeshTop, mModelMatTop, modelViewMat, mTexture);
	//renderFace(mMeshBot, mModelMatBot, modelViewMat, mTexture);
	//
	//// Dibujamos la cara trasera con la textura trasera
	//glCullFace(GL_FRONT);
	//renderFace(mMeshTop, mModelMatTop, modelViewMat, _innerTexture);
	//renderFace(mMeshBot, mModelMatBot, modelViewMat, _innerTexture);
	//
	//glDisable(GL_CULL_FACE);
}

void Box::renderFace(const Mesh* mesh, const glm::mat4& modelMat, const glm::mat4& modelViewMat, Texture* texture) const {
	if (mesh != nullptr) {
		glm::mat4 aMat = modelViewMat * modelMat; // glm matrix multiplication

		mShader->use();
		mShader->setUniform("modulate", mModulate); // Fijamos el uniform modulate con mModulate

		if (texture != nullptr) texture->bind(); // Le decimos a la GPU que utilice esta textura

		upload(aMat);
		mesh->render();

		if (texture != nullptr) texture->unbind(); // Le decimos a la GPU que ya no la tiene que utilizar
	}
}