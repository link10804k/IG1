#ifndef RGB_TRIANGLE_H
#define RGB_TRIANGLE_H

#include "Entity.h"

class RGBTriangle : public EntityWithColors {
public:
	RGBTriangle(GLuint r, GLdouble x, GLdouble y);
	~RGBTriangle() = default;
};

#endif

