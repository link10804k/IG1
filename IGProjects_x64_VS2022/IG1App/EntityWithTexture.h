#ifndef ENTITY_WITH_TEXTURE_H
#define ENTITY_WITH_TEXTURE_H

#include "Entity.h"

#include "Texture.h"

class EntityWithTexture : public Abs_Entity {
protected:
	Texture* mTexture = nullptr;
	bool mModulate = false;
public:
	EntityWithTexture();
	virtual ~EntityWithTexture();

	void setTexture(Texture* texture);
	virtual void render(const glm::mat4& modelViewMat) const override;
};

#endif

