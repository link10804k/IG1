#ifndef RGB_RECTANGLE_H
#define RGB_RECTANGLE_H

#include "Entity.h"

class RGBRectangle : public EntityWithColors {
public:
	RGBRectangle(GLdouble w, GLdouble h);
	~RGBRectangle() = default;

	void render(glm::mat4 const& modelViewMat) const override;
};

#endif

