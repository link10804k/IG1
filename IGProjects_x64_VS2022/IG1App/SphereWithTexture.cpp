#include "SphereWithTexture.h"

#include "IndexMesh.h"

SphereWithTexture::SphereWithTexture(GLdouble radius, GLuint nParallels, GLuint nMeridians) {
	mMesh = IndexMesh::generateSphere(radius, nParallels, nMeridians);
}
