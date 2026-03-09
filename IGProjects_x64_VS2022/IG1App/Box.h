#ifndef BOX_H
#define BOX_H

#include "BoxOutline.h"

class Box : public BoxOutline {
private:
	Mesh* mMeshTop;
	Mesh* mMeshBot;
	glm::mat4 mModelMatTop;
	glm::mat4 mModelMatBot;

	void renderFace(const Mesh* mesh, const glm::mat4& modelMat, const glm::mat4& modelViewMat, Texture* texture) const;
public:
	Box(GLdouble length);
	~Box() = default;

	void render(const glm::mat4& modelViewMat) const override;
};

#endif
