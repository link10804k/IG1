#include "Scene6.h"

#include "IndexedBox.h"
#include "Disk.h"
#include "Cone.h"
#include "Sphere.h"

void Scene6::init() {
	// Para el setGL() y las RGBAxis
	Scene::init();

	// Cubo
	//IndexedBox* ib = new IndexedBox(100);
	//ib->setColor({ 0, 1, 0, 1 });
	//gObjects.push_back(ib);

	// Disco
	//Disk* d = new Disk(200, 100, 2, 20);
	//d->setColor({ 0, 1, 0, 1 });
	//gObjects.push_back(d);

	// Cono
	//Cone* c = new Cone(200, 100, 0, 2, 20);
	//c->setColor({ 0, 1, 0, 1 });
	//gObjects.push_back(c);

	// Esfera
	Sphere* s = new Sphere(200, 20, 20);
	s->setColor({ 0, 1, 0, 1 });
	gObjects.push_back(s);
}