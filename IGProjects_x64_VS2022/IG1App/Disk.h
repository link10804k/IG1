#ifndef DISK_H
#define DISK_H

#include "ColorMaterialEntity.h"

class Disk : public ColorMaterialEntity {
public:
    Disk(GLdouble R, GLdouble r, GLuint nRings, GLuint nSamples);
    ~Disk() = default;
};

#endif