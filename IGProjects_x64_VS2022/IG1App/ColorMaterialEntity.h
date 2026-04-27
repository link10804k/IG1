#ifndef COLOR_MATERIAL_ENTITY_H
#define COLOR_MATERIAL_ENTITY_H

#include "EntityWithMaterial.h"

class ColorMaterialEntity : public EntityWithMaterial {
public:
	ColorMaterialEntity();
	virtual ~ColorMaterialEntity() = default;
	void render(const glm::mat4& modelViewMat) const override;

	static inline void toggleShowNormals() {
		mShowNormals = !mShowNormals;
	}

	void setColor(glm::vec4 color);
private:
	Shader* normalShader;
	inline static bool mShowNormals = false;
};

#endif

