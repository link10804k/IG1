#ifndef COLOR_MATERIAL_ENTITY_H
#define COLOR_MATERIAL_ENTITY_H

#include "SingleColorEntity.h"

class ColorMaterialEntity : public SingleColorEntity {
public:
	ColorMaterialEntity();
	virtual ~ColorMaterialEntity() = default;
	void render(const glm::mat4& modelViewMat) const override;
};

#endif

