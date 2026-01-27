#ifndef REGULAR_POLYGON_H
#define REGULAR_POLYGON_H

#include "SingleColorEntity.h"

class RegularPolygon : public SingleColorEntity {
public:
	RegularPolygon(GLuint num, GLdouble r, glm::vec4 mColor = {1, 1, 1, 1});
	~RegularPolygon() = default;
};

#endif

