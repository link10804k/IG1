#ifndef DROID_H
#define DROID_H

#include "CompoundEntity.h"

class SpotLight;

class Droid : public CompoundEntity {
public:
    Droid(GLdouble radius);
    virtual ~Droid();

    void walk();
    void render(const glm::mat4& modelViewMat) const override;

    void unloadLight();
    void setEnabledLight(bool enabled);
    bool getEnabledLight();
private:
    Abs_Entity* body = nullptr;
    SpotLight* droidLight = nullptr;
};

#endif