#include "Disk.h"

#include "IndexMesh.h"

#include <vector>

Disk::Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples) {
	std::vector<glm::vec2> profile;
	profile.reserve(nRings);

	GLdouble ini = R;
	GLdouble distance = R - r;

	for (int i = 0; i < nRings; ++i) {
		profile.emplace_back(ini, 0);
		ini -= distance / (nRings - 1);
	}

	mMesh = IndexMesh::generateByRevolution(profile, nSamples);
}
