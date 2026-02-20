#ifndef ENTITY_WITH_TEXTURE_H
#define ENTITY_WITH_TEXTURE_H

#include "Entity.h"

#include "Texture.h"

class EntityWithTexture : public Abs_Entity {
protected:
	Texture* mTexture = nullptr; // TODO: Liberar memoria depende de como se cree la textura
	bool mModulate = false;
public:
	EntityWithTexture();
	~EntityWithTexture();

	void render(const glm::mat4& modelViewMat) const override;
};

#endif

