#include "Droid.h"

#include "CompoundEntity.h"
#include "SphereWithTexture.h"
#include "Cone.h"
#include "Disk.h"
#include "TextureManager.h"

#include "glm/gtc/matrix_transform.hpp"

Droid::Droid(GLdouble radius) {
    // Cuerpo
	SphereWithTexture* cuerpoMesh = new SphereWithTexture(radius, 50, 50);
    cuerpoMesh->setTexture(TEXTURE_MANAGER->getTexture("container.jpg"));
    addEntity(cuerpoMesh);

    body = cuerpoMesh;

    // Cabeza
    CompoundEntity* cabeza = new CompoundEntity();
    cabeza->setModelMat(glm::translate(cabeza->modelMat(), glm::vec3(0, radius, 0)));
    addEntity(cabeza);

    Cone* cabezaMesh = new Cone(radius / 2, radius, radius / 2, 50, 50);
    cabezaMesh->setColor({1, 1, 0, 1});
    cabeza->addEntity(cabezaMesh);

    Disk* tapaCabezaMesh = new Disk(radius / 2, 0, 50, 50);
    tapaCabezaMesh->setColor({1, 1, 0, 1});
    tapaCabezaMesh->setModelMat(glm::translate(tapaCabezaMesh->modelMat(), glm::vec3(0, radius / 4, 0)));
    cabeza->addEntity(tapaCabezaMesh);

    //Ojos
    Cone* ojoIzqMesh = new Cone(radius / 2, radius / 12, radius / 12, 2, 50);
    ojoIzqMesh->setModelMat(glm::translate(ojoIzqMesh->modelMat(), glm::vec3(-radius / 10, 0, radius)));
    ojoIzqMesh->setModelMat(glm::rotate(ojoIzqMesh->modelMat(), glm::radians(90.0f), glm::vec3(1, 0, 0)));
    ojoIzqMesh->setColor({0, 1, 0, 1});
    cabeza->addEntity(ojoIzqMesh);
    
    Cone* ojoDerMesh = new Cone(radius / 2, radius / 12, radius / 12, 2, 50);
    ojoDerMesh->setModelMat(glm::translate(ojoDerMesh->modelMat(), glm::vec3(radius / 10, 0, radius)));
    ojoDerMesh->setModelMat(glm::rotate(ojoDerMesh->modelMat(), glm::radians(90.0f), glm::vec3(1, 0, 0)));
    ojoDerMesh->setColor({0, 1, 0, 1});
    cabeza->addEntity(ojoDerMesh);
}

void Droid::walk() {
    assert(body != nullptr);

    float angle = 5.0f;
    body->setModelMat(glm::rotate(body->modelMat(), glm::radians(angle), glm::vec3(1, 0, 0)));
}