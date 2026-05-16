#include "ColorMaterialEntity.h"

#include "IG1App.h"

void ColorMaterialEntity::setColor(glm::vec4 color) {
	setMaterial(Material(color));
}
