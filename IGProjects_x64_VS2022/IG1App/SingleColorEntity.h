#ifndef SINGLE_COLOR_ENTITY_H
#define SINGLE_COLOR_ENTITY_H

#include "Entity.h"

class SingleColorEntity : public Abs_Entity {
protected:
	glm::vec4 mColor = {1, 1, 1, 1};
public:
	SingleColorEntity(glm::vec4 mColor);
	void render(const glm::mat4& modelViewMat) const override;
	

	glm::vec4 getColor();
	void setColor(glm::vec4 mColor);
};

#endif

