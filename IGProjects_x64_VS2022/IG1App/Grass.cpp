#include "Grass.h"

#include "glm/gtc/matrix_transform.hpp"

Grass::Grass(GLdouble width, GLdouble height) {
	mMesh = Mesh::generateRectangleTexCor(width, height, 1, 1);

	mShader = Shader::get("texture:texture_alpha");
}

void Grass::render(const glm::mat4& modelViewMat) const {
	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		mShader->use();
		mShader->setUniform("modulate", mModulate); // Fijamos el uniform modulate con mModulate

		if (mTexture != nullptr) mTexture->bind(); // Le decimos a la GPU que utilice esta textura

		upload(aMat);
		mMesh->render();
		// Rotamos la aMat para renderizar la hierba rotada 120º en el eje y
		upload(glm::rotate(aMat, glm::radians(120.0f), glm::vec3(0, 1, 0)));
		mMesh->render();
		// Rotamos la aMat para renderizar la hierba rotada 240 en el eje y
		upload(glm::rotate(aMat, glm::radians(240.0f), glm::vec3(0, 1, 0)));
		mMesh->render();

		if (mTexture != nullptr) mTexture->unbind(); // Le decimos a la GPU que ya no la tiene que utilizar
	}
}