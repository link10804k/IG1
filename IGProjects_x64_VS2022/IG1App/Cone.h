#ifndef CONE_H
#define CONE_H

#include "ColorMaterialEntity.h"

class Cone : public ColorMaterialEntity {
public:
    Cone(GLdouble h, GLdouble r, GLuint R, GLuint nRings, GLuint nSamples);
    ~Cone() = default;
};

#endif