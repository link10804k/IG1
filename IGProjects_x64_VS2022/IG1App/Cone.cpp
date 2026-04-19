#include "Cone.h"

#include "IndexMesh.h"

#include <vector>

Cone::Cone(GLdouble h, GLdouble r, GLuint R, GLuint nRings, GLuint nSamples) {
	std::vector<glm::vec2> profile;
	profile.reserve(nRings);

	GLdouble x = r;
	GLdouble y = -(h / 2);
	GLdouble distanceX = R - r;
	GLdouble distanceY = h;

	for (int i = 0; i < nRings; ++i) {
		profile.emplace_back(x, y);
		x += distanceX / (nRings - 1);
		y += distanceY / (nRings - 1);
	}

	mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}
