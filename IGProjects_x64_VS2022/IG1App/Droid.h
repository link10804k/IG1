#ifndef DROID_H
#define DROID_H

#include "CompoundEntity.h"

class SpotLight;

class Droid : public CompoundEntity {
public:
    Droid(GLdouble radius);
    virtual ~Droid() = default;

    void walk();

    // Getter para que la escena inserte la luz del androide en gLights
    SpotLight* getDroidLight();
    void render(const glm::mat4& modelViewMat) const override;
private:
    Abs_Entity* body = nullptr;
    SpotLight* droidLight = nullptr;
};

#endif