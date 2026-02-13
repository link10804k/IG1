#include "RGBCube.h"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

RGBCube::RGBCube(GLdouble lenght) {
	mMesh = Mesh::generateRGBCubeTriangles(lenght);
}

// Rotamos 5º cada frame hasta llegar a 180º, momento en el que cambia su eje de rotación 
// y vuelve a hacer lo mismo (Esto se da en el eje 'x', el 'y' y el 'z' y al acabar con el último vuelve al primero)
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
