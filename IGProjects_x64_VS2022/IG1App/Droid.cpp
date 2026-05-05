#include "Droid.h"

#include "CompoundEntity.h"
#include "SphereWithTexture.h"
#include "Cone.h"
#include "Disk.h"
#include "TextureManager.h"

#include "glm/gtc/matrix_transform.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/matrix_decompose.hpp"

#include "Light.h"

#include "IG1App.h"

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

    // Luz
    droidLight = new SpotLight(glm::vec3(0, 0, 0), 1); // id 1 porque ya se crea otra SpotLight con id 0 en la escena
    droidLight->setEnabled(true);

    droidLight->setAmb({ 0.25, 0.25, 0.25 });
    droidLight->setDiff({ 0.6, 0.6, 0.6 });
    droidLight->setSpec({ 0, 0.2, 0 });

    droidLight->setPosition(glm::vec3(0, 0, 0));
    droidLight->setDirection(glm::vec3(0, -1, 0));
    droidLight->setCutoff(30.0f, 60.0f);
}
void Droid::render(const glm::mat4& modelViewMat) const {
    // Calculamos la matriz de modelado absoluta del androide (mModelMat es relativa a la de su padre, el nodo fantasma, 
    // por lo que necesitamos la modelViewMat que nos pasa el render y deshacer la multiplicación de la viewMat)
    glm::mat4 aMat = glm::inverse(IG1App::s_ig1app.camera().viewMat()) * modelViewMat * mModelMat;

    // Utilizamos la posición del androide para settear la posición de la luz ({0, 0, 0} es su posición inicial)
    droidLight->setPosition(aMat * glm::vec4(0, 0, 0, 1));
    // Utilizamos la orientación del androide para settear la dirección de la luz ({0, -1, 0} es su dirección inicial)
    droidLight->setDirection(aMat * glm::vec4(0, -1, 0, 0));

    CompoundEntity::render(modelViewMat);
}

void Droid::walk() {
    assert(body != nullptr);

    float angle = 5.0f;
    body->setModelMat(glm::rotate(body->modelMat(), glm::radians(angle), glm::vec3(1, 0, 0)));
}

SpotLight* Droid::getDroidLight() {
    return droidLight;
}
