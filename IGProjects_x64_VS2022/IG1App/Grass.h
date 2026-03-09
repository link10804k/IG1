#ifndef GRASS_H
#define GRASS_H

#include "EntityWithTexture.h"

class Grass : public EntityWithTexture {
public:
	Grass(GLdouble width, GLdouble height);
	~Grass() = default;

	void render(const glm::mat4& modelViewMat) const override;
};

#endif

