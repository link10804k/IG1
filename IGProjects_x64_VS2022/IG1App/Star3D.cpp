#include "Star3D.h"

#include "glm/gtc/matrix_transform.hpp"

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h) {
	mMesh = Mesh::generateStar3DTexCor(re, np, h);
}

void Star3D::render(const glm::mat4& modelViewMat) const {
	EntityWithTexture::render(modelViewMat);

	if (mMesh != nullptr) {
		glm::mat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication

		mShader->use();
		mShader->setUniform("modulate", mModulate); // Fijamos el uniform modulate con mModulate

		if (mTexture != nullptr) mTexture->bind(); // Le decimos a la GPU que utilice esta textura

		// Rotamos la aMat para renderizar la estrella rotada 180º en el eje y
		upload(glm::rotate(aMat, glm::radians(180.0f), glm::vec3(0, 1, 0)));
		mMesh->render();

		if (mTexture != nullptr) mTexture->unbind(); // Le decimos a la GPU que ya no la tiene que utilizar
	}
}

void Star3D::update() {
	float ang = glm::radians(5.0f);

	glm::vec3 pos = { mModelMat[3][0], mModelMat[3][1], mModelMat[3][2] };
	glm::translate(mModelMat, pos);
	mModelMat = glm::rotate(glm::mat4(1), ang, glm::vec3(0, 1, 0)) * mModelMat;
	mModelMat[3][0] = pos.x;
	mModelMat[3][1] = pos.y;
	mModelMat[3][2] = pos.z;


	mModelMat = glm::rotate(mModelMat, ang, glm::vec3(0, 0, 1));

}