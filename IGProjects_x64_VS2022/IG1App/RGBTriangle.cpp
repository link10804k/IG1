#include "RGBTriangle.h"
#include "RegularPolygon.h"

RGBTriangle::RGBTriangle(GLuint r) {
	mMesh = Mesh::generateRegularPolygon(3, r);

	std::vector<glm::vec4> colors(3);

	for (size_t i = 0; i < colors.size(); ++i) {
		colors[i][i] = 1;
		colors[i][3] = 1;
	}
	mMesh->setVerticesColors(colors);
}