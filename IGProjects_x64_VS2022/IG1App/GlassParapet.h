#ifndef GLASS_PARAPET_H
#define GLASS_PARAPET_H

#include "EntityWithTexture.h"
class GlassParapet : public EntityWithTexture {
public:
	GlassParapet(GLdouble length);
	~GlassParapet() = default;
};

#endif

