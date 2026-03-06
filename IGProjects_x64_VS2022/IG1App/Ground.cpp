#include "Ground.h"

#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"

Ground::Ground(GLdouble w, GLdouble d, GLuint rw, GLuint rh) {
	mMesh = Mesh::generateRectangleTexCor(w, d, rw, rh);
	float ang = glm::radians(90.0f);
	
	mModelMat = glm::rotate(glm::mat4(1), ang, glm::vec3(1, 0, 0)) * mModelMat;
}

Ground::~Ground() {
	delete mTexture;
}

void Ground::setTexture(Texture* texture) {
	// ASK: Nos da un error de la textura repetidamente
	mTexture = texture;
}