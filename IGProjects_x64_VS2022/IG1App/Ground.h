#ifndef GROUND_H
#define GROUND_H

#include "Entity.h"

class Ground : public EntityWithColors {
public:
	Ground(GLdouble w, GLdouble d);
	~Ground() = default;

	void render(glm::mat4 const& modelViewMat) const override;
};

#endif

