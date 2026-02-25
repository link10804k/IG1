#ifndef BOX_OUTLINE_H
#define BOX_OUTLINE_H

#include "SingleColorEntity.h"
class BoxOutline : public SingleColorEntity {
public:
	BoxOutline(GLdouble length);
	~BoxOutline() = default;

	void render(const glm::mat4& modelViewMat) const override;
};

#endif

