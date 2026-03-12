#ifndef BOX_H
#define BOX_H

#include "BoxOutline.h"

class Box : public BoxOutline {
private:
	Mesh* mMeshLid;
	GLdouble length;
	float lidRotation = 0.0f;
	bool rotationDirection = true; // Indica si la rotación es positiva o negativa

	void renderFace(const glm::mat4& modelViewMat, Texture* texture) const;
public:
	Box(GLdouble length);
	~Box();

	void render(const glm::mat4& modelViewMat) const override;
	void update() override;

	void load() override;
	void unload() override;
};

#endif
