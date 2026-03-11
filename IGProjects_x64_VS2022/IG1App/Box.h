#ifndef BOX_H
#define BOX_H

#include "BoxOutline.h"

class Box : public BoxOutline {
private:
	Mesh* mMeshLid;
	GLdouble length;

	void renderFace(const glm::mat4& modelViewMat, Texture* texture) const;
public:
	Box(GLdouble length);
	~Box();

	void render(const glm::mat4& modelViewMat) const override;
	// TODO: Hacer el update

	void load() override;
	void unload() override;
};

#endif
