#ifndef RGB_TRIANGLE_H
#define RGB_TRIANGLE_H

#include "Entity.h"

class RGBTriangle : public EntityWithColors {
private:
	GLfloat totalAngle = 0;
public:
	RGBTriangle(GLuint r);
	~RGBTriangle() = default;

	void update() override;
};

#endif

