#ifndef DROID_H
#define DROID_H

#include "CompoundEntity.h"

class Droid : public CompoundEntity {
public:
    Droid(GLdouble radius);
    virtual ~Droid() = default;

    void walk();
private:
    Abs_Entity* body = nullptr;
};

#endif