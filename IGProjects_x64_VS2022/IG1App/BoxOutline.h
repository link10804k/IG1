#ifndef BOX_OUTLINE_H
#define BOX_OUTLINE_H

#include "EntityWithTexture.h"

class BoxOutline : public EntityWithTexture {
protected:
	Texture* _innerTexture = nullptr;
	void renderFace(const glm::mat4& modelViewMat, Texture* texture) const;
public:
	BoxOutline(GLdouble length);
	virtual ~BoxOutline() = default;

	void setTexture(Texture* externTexture, Texture* innerTexture);
	void render(const glm::mat4& modelViewMat) const override;
};

#endif

