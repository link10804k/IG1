#ifndef COLOR_MATERIAL_ENTITY_H
#define COLOR_MATERIAL_ENTITY_H

#include "SingleColorEntity.h"

class ColorMaterialEntity : public SingleColorEntity {
public:
	ColorMaterialEntity();
	virtual ~ColorMaterialEntity() = default;
	void render(const glm::mat4& modelViewMat) const override;

	static inline void toggleShowNormals() {
		mShowNormals = !mShowNormals;
	}
private:
	Shader* normalShader;
	// ASK: ¿inline está bien? Si no se pone inline no deja asignarle falso por no ser constante
	inline static bool mShowNormals = false;
};

#endif

