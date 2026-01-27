#ifndef RGB_RECTANGLE_H
#define RGB_RECTANGLE_H

#include "Entity.h"

class RGBRectangle : public EntityWithColors {
public:
	RGBRectangle(GLdouble w, GLdouble h) {
		mMesh = Mesh::generateRGBRectangle(w, h);
	}
};

#endif

