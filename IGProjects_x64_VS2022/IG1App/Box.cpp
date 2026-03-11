#include "Box.h"

#include "glm/gtc/matrix_transform.hpp"

Box::Box(GLdouble length) : BoxOutline(length), length(length) {
	assert(mMesh != nullptr);

	mMeshLid = Mesh::generateRectangleTexCor(length, length, 1, 1);
}

Box::~Box() {
	delete mMeshLid;
}

void Box::render(const glm::mat4& modelViewMat) const {
	BoxOutline::render(modelViewMat);

	glEnable(GL_CULL_FACE);
	// Dibujamos la cara frontal con la textura frontal
	glCullFace(GL_BACK);
	renderFace(modelViewMat, mTexture);
	
	// Dibujamos la cara trasera con la textura trasera
	glCullFace(GL_FRONT);
	renderFace(modelViewMat, _innerTexture);
	
	glDisable(GL_CULL_FACE);
}

void Box::renderFace(const glm::mat4& modelViewMat, Texture* texture) const {
	if (mMesh != nullptr && mMeshLid != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		mShader->use();
		mShader->setUniform("modulate", mModulate); // Fijamos el uniform modulate con mModulate

		if (texture != nullptr) texture->bind(); // Le decimos a la GPU que utilice esta textura

		upload(aMat);
		mMesh->render();

		glm::mat4 topModelMat = glm::rotate(glm::translate(mModelMat, glm::vec3(0, length / 2, 0)), glm::radians(-90.0f), glm::vec3(1, 0, 0));
		glm::mat4 botModelMat = glm::rotate(glm::translate(mModelMat, glm::vec3(0, -length / 2, 0)), glm::radians(90.0f), glm::vec3(1, 0, 0));

		aMat = modelViewMat * topModelMat;

		upload(aMat);
		mMeshLid->render();

		aMat = modelViewMat * botModelMat;

		upload(aMat);
		mMeshLid->render();

		if (texture != nullptr) texture->unbind(); // Le decimos a la GPU que ya no la tiene que utilizar
	}
}

void Box::load() {
	mMesh->load();
	mMeshLid->load();
}

void Box::unload() {
	mMesh->unload();
	mMeshLid->unload();
}