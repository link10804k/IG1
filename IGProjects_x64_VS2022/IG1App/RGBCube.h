#ifndef RGBCube_H
#define RGBCube_H

#include "Entity.h"

class RGBCube : public EntityWithColors {
private:
    int frame = 0;

public:
    RGBCube(GLdouble lenght);
    ~RGBCube() = default;
    void update() override;
};

#endif

