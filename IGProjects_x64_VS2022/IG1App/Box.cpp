#include "Box.h"

#include "glm/gtc/matrix_transform.hpp"

Box::Box(GLdouble length) : BoxOutline(length), length(length) {
	assert(mMesh != nullptr);

	mMeshLid = Mesh::generateRectangleTexCor(length, length, 1, 1);
}

Box::~Box() {
	delete mMeshLid;
	mMeshLid = nullptr;
}

void Box::update() {
	if (rotationDirection) {
		lidRotation += 5.0f;

		// Cuando llega a 180º, se invierte la rotación
		if (lidRotation >= 180.0f) rotationDirection = false;
	}
	else {
		lidRotation -= 5.0f;

		// Cuando llega a 0º, se invierte la rotación
		if (lidRotation <= 0.0f) rotationDirection = true;
	}
}

void Box::render(const glm::mat4& modelViewMat) const {
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

		// Rotamos -90 grados para dejar el rectángulo como una tapa
		glm::mat4 topModelMat = glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(1, 0, 0));
		// Trasladamos la mitad de su longitud para dejar el rectángulo pegado al (0,0,0)
		topModelMat = glm::translate(topModelMat, glm::vec3(length / 2, 0, 0));
		// Rotamos el rectángulo en el eje z con el (0,0,0) como orígen
		topModelMat = glm::rotate(glm::mat4(1), glm::radians(lidRotation), glm::vec3(0, 0, 1)) * topModelMat;
		
		// Trasladamos el rectángulo a la posición de la caja
		topModelMat = glm::translate(mModelMat, glm::vec3(-length / 2, length / 2, 0)) * topModelMat;

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