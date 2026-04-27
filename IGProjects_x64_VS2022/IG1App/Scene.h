#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Light.h"

#include <vector>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene();

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	virtual void init();

	void render(Camera const& cam) const;
	void update();

	// load or unload scene data into the GPU
	void load();
	void unload();

	void scene();

	// CNG: Adiciones para rotar el androide
	virtual void rotate() {}
	virtual void orbit() {}

	// CNG: Input escena
	virtual void handleInput(char c) {}
protected:
	void destroy();
	void setGL();
	virtual void setBackgroundColor();
	void resetGL();

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> gTranslucidObjects; // CNG: Entidades translúcidas de la escena
	std::vector<Light*> gLights; // CNG: Entidades de luz

	void uploadLights() const;
	DirLight* dirLight = nullptr;
};

#endif //_H_Scene_H_
