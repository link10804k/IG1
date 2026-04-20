#include "CompoundEntity.h"

CompoundEntity::~CompoundEntity(){
    for (Abs_Entity* child : gObjects){
        delete child;
    }
    gObjects.clear();
}

void CompoundEntity::addEntity(Abs_Entity* entity){
    gObjects.push_back(entity);
}

void CompoundEntity::render(const glm::mat4& modelViewMat) const {
    glm::mat4 aMat = modelViewMat * mModelMat;
    for (Abs_Entity* child : gObjects) {
        child->render(aMat);
    }
}
void CompoundEntity::update() {
    for (Abs_Entity* child : gObjects) {
        child->update();
    }
}

void CompoundEntity::load() {
    for (Abs_Entity* child : gObjects) {
        child->load();
    }
}
void CompoundEntity::unload() {
    for (Abs_Entity* child : gObjects) {
        child->unload();
    }
}