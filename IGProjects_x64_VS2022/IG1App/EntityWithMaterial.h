#ifndef ENTITY_WITH_MATERIAL_H
#define ENTITY_WITH_MATERIAL_H

#include "Entity.h"

#include "Material.h"

class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial();
	virtual ~EntityWithMaterial() = default;
	void setMaterial(const Material& m) { mMaterial = m; };
	void render(const glm::mat4& modelViewMat) const override;

	static inline void toggleShowNormals() {
		mShowNormals = !mShowNormals;
	}
protected:
	Material mMaterial;
	Shader* normalShader;
	inline static bool mShowNormals = false;
};

#endif

