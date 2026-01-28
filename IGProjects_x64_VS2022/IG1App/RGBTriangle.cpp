#include "RGBTriangle.h"
#include "RegularPolygon.h"

RGBTriangle::RGBTriangle(GLuint r, GLdouble x, GLdouble y) {
	mMesh = Mesh::generateTriangleWithColors(r, x, y);
}