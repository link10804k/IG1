#pragma once

#include "Mesh.h"

#include <vector>
#include <numbers>

class IndexMesh : public Mesh {
private:
	std::vector<GLuint> vIndexes;
	GLuint mIBO;

	void draw() const override;
public:
	void load() override;
	void unload() override;

	// profile: vector de vértices que representa el perfil de la figura en los ejes XY
	// nSamples: número de muestras que conforman la figura
	// angleMax: ángulo de rotación de la figura completa
	static IndexMesh* generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax = 2 * std::numbers::pi);

	static IndexMesh* generateIndexedBox8(GLdouble l);
	static IndexMesh* generateIndexedBox(GLdouble l);

	void buildNormalVectors();
};

