#ifndef _H_RGBCube_H_

#include "Entity.h"
class RGBCube : public EntityWithColors
{
private:
    int frame = 0;

public:
    RGBCube(GLdouble lenght);
    ~RGBCube() = default;
    void update() override;
};


#endif // !_H_RGBCube_H_

