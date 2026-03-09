#include "GlassParapet.h"

GlassParapet::GlassParapet(GLdouble length) {
	mMesh = Mesh::generateBoxOutlineTexCor(length);
}

