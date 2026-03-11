#ifndef PHOTO_H
#define PHOTO_H

#include "EntityWithTexture.h"

class Photo : public EntityWithTexture {
public:
	Photo(GLdouble w, GLdouble d);
	~Photo();

	void update() override;
};

#endif

