#include "Torus.h"

#include "IndexMesh.h"

#include <vector>

Torus::Torus(GLdouble R, GLdouble r, GLuint nPoints, GLuint nSamples) {
    std::vector<glm::vec2> profile;
	profile.reserve(nPoints);

	GLdouble centerX = R;
	GLdouble centerY = 0;

	GLdouble angleCount = glm::radians(270.0f);
	// Se colocan los vértices siguiendo una circunferencia
	for (GLuint i = 0; i < nPoints; ++i) {
		GLdouble x = centerX + r * glm::cos(angleCount);
		GLdouble y = centerY + r * glm::sin(angleCount);
		profile.emplace_back(x, y);

		angleCount += glm::radians(360.0 / nPoints - 1);
	}

	for (glm::vec2 vertex : profile) {
		printf("x: %f y: %f\n", vertex.x, vertex.y);
	}

    mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}