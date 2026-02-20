#ifndef GROUND_H
#define GROUND_H

#include "EntityWithTexture.h"

class Ground : public EntityWithTexture {
public:
	Ground(GLdouble w, GLdouble d, GLuint rw, GLuint rh);
	~Ground();

	void setTexture(Texture* texture);
};

#endif

