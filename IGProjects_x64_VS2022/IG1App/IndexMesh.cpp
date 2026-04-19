#include "IndexMesh.h"

#include <algorithm>

void IndexMesh::draw() const {
	glDrawElements(
		mPrimitive, // primitiva ( GL_TRIANGLES , etc.)
		vIndexes.size(), // número de índices
		GL_UNSIGNED_INT, // tipo de los índices
		nullptr // offset en el VBO de índices
	);
}

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = std::numeric_limits<GLuint>::max();

void IndexMesh::load() {
	Mesh::load(); 
	glBindVertexArray(mVAO);
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		vIndexes.size() * sizeof(GLuint),
		vIndexes.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}
void IndexMesh::unload() {
	if (mVAO == NONE) return;

	Mesh::unload();

	if (mIBO != NONE) {
		glDeleteBuffers(1, &mIBO);
		mIBO = NONE;
	}
}

void IndexMesh::buildNormalVectors() {
	int n = vVertices.size();
	int m = vIndexes.size();

	vNormals.clear();
	vNormals.resize(mNumVertices, {  0.0, 0.0, 0.0 });

	for (int k = 0; k < m; k += 3) {
		glm::vec3 normal = normalize(cross(vVertices[vIndexes[k + 1]] - vVertices[vIndexes[k]], vVertices[vIndexes[k + 2]] - vVertices[vIndexes[k]]));
		vNormals[vIndexes[k]] += normal;
		vNormals[vIndexes[k   + 1]] += normal;
		vNormals[vIndexes[k   + 2]] += normal;
	}
	for (int j = 0; j < n; ++j) {
		vNormals[j] = normalize(vNormals[j]);
	}
}

IndexMesh* IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax) {
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;
	int tamPerfil = profile.size();
	mesh->vVertices.reserve(nSamples * tamPerfil);

	// Genera los vértices de las muestras
	GLdouble theta1 = angleMax / nSamples;

	for (int i = 0; i <= nSamples; ++i) { // muestra i-ésima
		GLdouble c = cos(i * theta1), s = sin(i * theta1);

		for (auto p : profile) // rota el perfil
			mesh->vVertices.emplace_back(p.x * c, p.y, -p.x * s);
	}
	
	// Si k == 1 significa que el cuerpo de revolución se tiene que cerrar por el final por lo que este for da una vuelta de menos para dejar la vuelta especial para otro bucle for
	int k = angleMax - 2 * (float)std::numbers::pi <= std::numeric_limits<float>::epsilon();

	for (int i = 0; i < nSamples - k; ++i){ // caras i a i + 1
		for (int j = 0; j < tamPerfil - 1; ++j) { // una cara
			if (profile[j].x != 0.0) // triángulo inferior
				for (auto [s, t] : { std::pair{i, j}, {i + 1, j}, {i, j + 1} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
			if (profile[j + 1].x != 0.0) // triángulo superior
				for (auto [s, t] : { std::pair{i, j + 1}, {i + 1, j}, {i + 1, j + 1} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
		}
	}

	if (k) {
		for (int j = 0; j < tamPerfil - 1; ++j) { // una cara
			int i = nSamples - 1;
			if (profile[j].x != 0.0) // triángulo inferior
				for (auto [s, t] : { std::pair{i, j}, {(i + 1) % nSamples, j}, {i, j + 1} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
			if (profile[j + 1].x != 0.0) // triángulo superior
				for (auto [s, t] : { std::pair{i, j + 1}, {(i + 1) % nSamples, j}, {(i + 1) % nSamples, j + 1} })
					mesh->vIndexes.push_back(s * tamPerfil + t);
		}
	}
		
		
	mesh->mNumVertices = mesh->vVertices.size();

	// Buildeamos sus normales
	mesh->buildNormalVectors();

	return mesh;
}

IndexMesh* IndexMesh::generateIndexedBox8(GLdouble l){
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 8;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vIndexes.reserve(36);

	mesh->vVertices.emplace_back(l, l, -l);
	mesh->vVertices.emplace_back(l, -l, -l);
	mesh->vVertices.emplace_back(l, l, l);
	mesh->vVertices.emplace_back(l, -l, l);
	mesh->vVertices.emplace_back(-l, l, l);
	mesh->vVertices.emplace_back(-l, -l, l);
	mesh->vVertices.emplace_back(-l, l, -l);
	mesh->vVertices.emplace_back(-l, -l, -l);

	// TODO: Están mása o menos las normales
	mesh->vIndexes = {  0, 1, 2, 2, 1, 3, 
						2, 3, 4, 4, 3, 5, 
						4, 5, 6, 6, 5, 7, 
						6, 7, 0, 0, 7, 1, 
						4, 6, 2, 2, 6, 0, 
						1, 7, 3, 3, 7, 5 };

	std::reverse(mesh->vIndexes.begin(), mesh->vIndexes.end());
	
	mesh->buildNormalVectors();

	return mesh;
}

IndexMesh* IndexMesh::generateIndexedBox(GLdouble l) {
	IndexMesh* mesh = new IndexMesh;
	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 24;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vIndexes.reserve(36);

	mesh->vVertices.emplace_back(l, l, -l); // 0
	mesh->vVertices.emplace_back(l, -l, -l); // 1
	mesh->vVertices.emplace_back(l, l, l); // 2
	mesh->vVertices.emplace_back(l, -l, l); // 3

	mesh->vVertices.emplace_back(l, l, l); // 2
	mesh->vVertices.emplace_back(l, -l, l); // 3
	mesh->vVertices.emplace_back(-l, l, l); // 4
	mesh->vVertices.emplace_back(-l, -l, l); // 5

	mesh->vVertices.emplace_back(-l, l, l); // 4
	mesh->vVertices.emplace_back(-l, -l, l); // 5
	mesh->vVertices.emplace_back(-l, l, -l); // 6
	mesh->vVertices.emplace_back(-l, -l, -l); // 7

	mesh->vVertices.emplace_back(-l, l, -l); // 6
	mesh->vVertices.emplace_back(-l, -l, -l); // 7
	mesh->vVertices.emplace_back(l, l, -l); // 0
	mesh->vVertices.emplace_back(l, -l, -l); // 1

	mesh->vVertices.emplace_back(-l, l, l); // 4
	mesh->vVertices.emplace_back(-l, l, -l); // 6
	mesh->vVertices.emplace_back(l, l, l); // 2
	mesh->vVertices.emplace_back(l, l, -l); // 0

	mesh->vVertices.emplace_back(l, -l, -l); // 1
	mesh->vVertices.emplace_back(-l, -l, -l); // 7
	mesh->vVertices.emplace_back(l, -l, l); // 3
	mesh->vVertices.emplace_back(-l, -l, l); // 5

	// TODO: Están mása o menos las normales
	// 0, 1, 2, 2, 1, 3
	mesh->vIndexes = { 0, 1, 2, 2, 1, 3,
						4, 5, 6, 6, 5, 7,
						8, 9, 10, 10, 9, 11,
						12, 13, 14, 14, 13, 15,
						16, 17, 18, 18, 17, 19,
						20, 21, 22, 22, 21, 23 };

	std::reverse(mesh->vIndexes.begin(), mesh->vIndexes.end());

	mesh->buildNormalVectors();

	return mesh;
}

