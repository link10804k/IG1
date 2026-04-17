#include "IndexMesh.h"

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

IndexMesh* IndexMesh::generateByRevolution(const std::vector<glm::vec2>& profile, GLuint nSamples, GLfloat angleMax) {
		IndexMesh* mesh = new IndexMesh;
		mesh->mPrimitive = GL_TRIANGLES;
		int tamPerfil = profile.size();
		mesh->vVertices.reserve(nSamples * tamPerfil);
		// Genera los vértices de las muestras
		GLdouble theta1 = 2 * std::numbers::pi / nSamples;
		for (int i = 0; i <= nSamples; ++i) { // muestra i-ésima
			GLdouble c = cos(i * theta1), s = sin(i * theta1);
			for (auto p : profile) // rota el perfil
				mesh->vVertices.emplace_back(p.x * c, p.y, -p.x * s);
			for (int i = 0; i < nSamples; ++i) // caras i a i + 1
				for (int j = 0; j < tamPerfil - 1; ++j) { // una cara
					if (profile[j].x != 0.0) // triángulo inferior
						for (auto [s, t] : { std::pair{i, j}, {i + 1, j}, {i, j + 1} })
							mesh->vIndexes.push_back(s * tamPerfil + t);
					if (profile[j + 1].x != 0.0) // triángulo superior
						for (auto [s, t] : { std::pair{i, j + 1}, {i + 1, j}, {i + 1, j + 1} })
							mesh->vIndexes.push_back(s * tamPerfil + t);
				}
		}
		mesh->mNumVertices = mesh->vVertices.size();

		// Buildeamos sus normales
		mesh->buildNormalVectors();

		return mesh;
	}

void IndexMesh::buildNormalVectors() {
	int n = vVertices.size();
	int m = vIndexes.size();

	vNormals.clear();
	vNormals.resize(mNumVertices, {0.0, 0.0, 0.0});

	for (int k = 0; k < m; k += 3) {
		glm::vec3 normal = normalize(cross(vVertices[vIndexes[k + 1]] - vVertices[vIndexes[k]], vVertices[vIndexes[k + 2]] - vVertices[vIndexes[k]]));
		vNormals[vIndexes[k]] += normal;
		vNormals[vIndexes[k+1]] += normal;
		vNormals[vIndexes[k+2]] += normal;
	}	
	for (int j = 0; j < n; ++j) {
		vNormals[j] = normalize(vNormals[j]);
	}
}

	
