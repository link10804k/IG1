#ifndef COLOR_MATERIAL_ENTITY_H
#define COLOR_MATERIAL_ENTITY_H

#include "EntityWithMaterial.h"

class ColorMaterialEntity : public EntityWithMaterial {
public:
	ColorMaterialEntity() = default;
	virtual ~ColorMaterialEntity() = default;
	void setColor(glm::vec4 color);
};

#endif

