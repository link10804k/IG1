#include "RGBTriangle.h"
#include "RegularPolygon.h"

RGBTriangle::RGBTriangle(GLuint r) {
	mMesh = Mesh::generateTriangleWithColors(r);
}