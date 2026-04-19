#include "Sphere.h"

#include "IndexMesh.h"

#include <vector>

Sphere::Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians) {
	std::vector<glm::vec2> profile;
	profile.reserve(nParallels);
	
	GLdouble angleCount = glm::radians(270.0f);
	// Se colocan los vértices siguiendo una semicircunferencia
	for (GLuint i = 0; i <= nParallels; ++i) {
		GLdouble x = radius * glm::cos(angleCount);
		GLdouble y = radius * glm::sin(angleCount);
		profile.emplace_back(x, y);
	
		angleCount += glm::radians(180.0 / nParallels);
	}
	//profile.emplace_back(0, radius);

	mMesh = IndexMesh::generateByRevolution(profile, nMeridians * 2);
}
