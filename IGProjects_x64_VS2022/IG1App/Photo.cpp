#include "Photo.h"

#include "glm/gtc/matrix_transform.hpp"

#include "IG1App.h"

Photo::Photo(GLdouble w, GLdouble d) {
	mMesh = Mesh::generateRectangleTexCor(w, d, 1, 1);

	mTexture = new Texture();
}

Photo::~Photo() {
	delete mTexture;
}

void Photo::update() {
	mTexture->loadColorBuffer(IG1App::s_ig1app.viewPort().width(), IG1App::s_ig1app.viewPort().height());
}
