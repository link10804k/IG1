#ifndef PHOTO_H
#define PHOTO_H

#include "EntityWithTexture.h"

class Photo : public EntityWithTexture {
public:
	Photo(GLdouble w, GLdouble d);
	~Photo() = default;

	void update() override;
};

#endif

