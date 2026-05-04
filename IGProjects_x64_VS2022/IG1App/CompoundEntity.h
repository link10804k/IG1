#ifndef COMPOUND_ENTITY_H
#define COMPOUND_ENTITY_H

#include "Entity.h"

class CompoundEntity : public Abs_Entity {
protected:
	std::vector<Abs_Entity*> gObjects;
public:
	CompoundEntity() = default;
	virtual ~CompoundEntity();

	void addEntity(Abs_Entity* entity);

	void render(const glm::mat4& modelViewMat) const override;
	void update() override;

	void load() override;
	void unload() override;
};

#endif
