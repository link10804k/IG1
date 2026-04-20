#ifndef SCENE8_H
#define SCENE8_h

#include "Scene.h"

class Droid;
class CompoundEntity;

class Scene8 : public Scene {
public:
	void init() override;

	void rotate() override;
	void orbit() override;
private:
	CompoundEntity* ghost = nullptr;
	Droid* droid = nullptr;
};

#endif

