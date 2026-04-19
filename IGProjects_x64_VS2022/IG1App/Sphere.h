#ifndef SPHERE_H
#define SPHERE_H

#include "ColorMaterialEntity.h"

class Sphere : public ColorMaterialEntity {
public:
    Sphere(GLdouble radius, GLuint nParallels, GLuint nMeridians);
    ~Sphere() = default;
};

#endif