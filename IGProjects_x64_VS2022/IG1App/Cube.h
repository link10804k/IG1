#ifndef _H_CUBE_H_
#define _H_CUBE_H_

#include "SingleColorEntity.h"


class Cube : public SingleColorEntity
{
public:
	Cube(GLdouble lenght);
	~Cube() = default;

	void render(const glm::mat4 &modelViewMat) const override;

};

#endif // !_H_CUBE_H_
