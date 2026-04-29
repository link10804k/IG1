#ifndef SCENE8_H
#define SCENE8_h

#include "Scene.h"

class Droid;
class CompoundEntity;

class Scene8 : public Scene {
public:
	void init() override;
	void setBackgroundColor() override;

	bool handleInput(char c) override;
private:
	void rotate() override;
	void orbit() override;

	CompoundEntity* ghost = nullptr;
	Droid* droid = nullptr;
};

#endif

