#include "Photo.h"

#include "glm/gtc/matrix_transform.hpp"

#include "IG1App.h"

Photo::Photo(GLdouble w, GLdouble d) {
	mMesh = Mesh::generateRectangleTexCor(w, d, 1, 1);
	float ang = glm::radians(90.0f);

	mModelMat = glm::rotate(glm::mat4(1), ang, glm::vec3(1, 0, 0)) * mModelMat;

	mTexture = new Texture();
}

Photo::~Photo() {
	delete mTexture;
}

void Photo::update() {
	mTexture->loadColorBuffer(IG1App::s_ig1app.viewPort().width(), IG1App::s_ig1app.viewPort().height());
}
