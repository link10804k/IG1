#include "ColorMaterialEntity.h"

#include "IG1App.h"

void ColorMaterialEntity::setColor(glm::vec4 color) {
	mMaterial.setAmb(color);
	mMaterial.setDiff(color);
	mMaterial.setSpec(color);
	mMaterial.setExp(1);
}
