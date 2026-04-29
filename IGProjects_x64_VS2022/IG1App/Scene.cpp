#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IG1App.h"

#include "Light.h"

using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene
	gObjects.push_back(new RGBAxes(400.0));

	// CNG: Luz direccional global
	dirLight = new DirLight();
	dirLight->setEnabled(true);

	dirLight->setAmb({ 0.25, 0.25, 0.25 });
	dirLight->setDiff({ 0.6, 0.6, 0.6 });
	dirLight->setSpec({ 0, 0.2, 0 });

	gLights.push_back(dirLight);
}

Scene::~Scene()
{
	destroy();
	resetGL();
}

void
Scene::destroy()
{ // release memory and resources

	// CNG
	for (Light* l : gLights)
		delete l;
	for (Abs_Entity* el : gObjects)
		delete el;
	for (Abs_Entity* obj : gTranslucidObjects)
		delete obj;

	gObjects.clear();
	gTranslucidObjects.clear();
}

void
Scene::load()
{
	setBackgroundColor();

	for (Abs_Entity* obj : gObjects)
		obj->load();
	for (Abs_Entity* obj : gTranslucidObjects)
		obj->load();
}

void
Scene::unload()
{
	// FIXME: Código dudoso
	Shader* s = Shader::get("light");
	for (Light* l : gLights) {
		l->unload(*s);
	}
	for (Abs_Entity* obj : gObjects)
		obj->unload();
	for (Abs_Entity* obj : gTranslucidObjects)
		obj->unload();
}

void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void
Scene::render(Camera const& cam) const
{
	// CNG
	uploadLights();

	cam.upload();

	for (Abs_Entity* el : gObjects)
		el->render(cam.viewMat());
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	for (Abs_Entity* el : gTranslucidObjects)
		el->render(cam.viewMat());

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

void Scene::update() {
	for (Abs_Entity* el : gObjects) {
		el->update();
	}
	for (Abs_Entity* el : gTranslucidObjects) {
		el->update();
	}
}

// FIXME: Código dudoso
void Scene::uploadLights() const {
	Shader* s = Shader::get("light");
	for (Light* l : gLights) {
		l->upload(*s, IG1App::s_ig1app.camera().viewMat());
	}
}

void Scene::setBackgroundColor(){
	glClearColor(0.6f, 0.7f, 0.8f, 1.0f);
}

bool Scene::handleInput(char c) {
	switch (c) {
	case 'r':
		dirLight->setEnabled(!dirLight->enabled());
		return true;
	}
}