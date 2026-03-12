#ifndef STAR3D_H
#define STAR3D_H

#include "EntityWithTexture.h"

class Star3D : public EntityWithTexture {
public:
	Star3D(GLdouble re, GLuint np, GLdouble h);
	~Star3D() = default;

	void render(const glm::mat4& modelViewMat) const override;
	void update() override;
};

#endif

