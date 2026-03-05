#ifndef GLASS_PARAPET_H
#define GLASS_PARAPET_H

#include "EntityWithTexture.h"
class GlassParapet : public EntityWithTexture {
public:
	GlassParapet();
	virtual ~GlassParapet() = default;

	void render(const glm::mat4& modelViewMat) const override;
};

#endif

