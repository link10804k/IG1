#include "Star3D.h"

#include "glm/gtc/matrix_transform.hpp"

Star3D::Star3D(GLdouble re, GLuint np, GLdouble h) {
	mMesh = Mesh::generateStar3DTexCor(re, np, h);
}

void Star3D::render(const glm::mat4& modelViewMat) const {
	EntityWithTexture::render(modelViewMat);

	// Rotamos la matriz de vista en el eje y para que se vea el modelo rotado en el eje y
	EntityWithTexture::render(glm::rotate(modelViewMat, glm::radians(180.0f), glm::vec3(0, 1, 0)));
}

void Star3D::update() {
	float ang = glm::radians(5.0f);
	mModelMat = glm::rotate(glm::mat4(1), ang, glm::vec3(0, 1, 0)) * mModelMat;
	mModelMat = glm::rotate(mModelMat, ang, glm::vec3(0, 0, 1));

}