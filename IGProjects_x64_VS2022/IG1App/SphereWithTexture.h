#ifndef SPHERE_WITH_TEXTURE_H
#define SPHERE_WITH_TEXTURE_H

#include "EntityWithTexture.h"

class SphereWithTexture : public EntityWithTexture {
public:
	SphereWithTexture(GLdouble radius, GLuint nParallels, GLuint nMeridians);
	~SphereWithTexture() = default;
};

#endif
