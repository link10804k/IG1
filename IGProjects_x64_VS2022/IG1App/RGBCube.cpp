#include "RGBCube.h"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

RGBCube::RGBCube(GLdouble lenght) {
	mMesh = Mesh::generateRGBCubeTriangles(lenght);
	mModelMat = glm::translate(mModelMat,glm::vec3(lenght/2, lenght /2, -lenght /2));
}
void RGBCube::update() {
	std::vector<glm::vec3> states = {
		{1,0,0},
		{0,0,1},
		{0,1,0}
	};

	GLfloat ang = glm::radians(5.0f);

	mModelMat = glm::rotate(glm::mat4(1), ang, states[frame/36]) * mModelMat;

	frame = (frame + 1) % 108;

}
