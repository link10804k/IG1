#include "Mesh.h"



using namespace std;
using namespace glm;

#define PUSH_V(x1,y1,z1,x2,y2,z2,x3,y3,z3) mesh->vVertices.emplace_back(x1,y1,z1); \
mesh->vVertices.emplace_back(x2,y2,z2); \
mesh->vVertices.emplace_back(x3,y3,z3) \

#define PUSH_TRIANGLE(V1,V2,V3) mesh->vVertices.emplace_back(V1.x, V1.y,V1.z); \
mesh->vVertices.emplace_back(V2.x, V2.y,V2.z); \
mesh->vVertices.emplace_back(V3.x, V3.y,V3.z) \

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

Mesh::Mesh()
 : mVAO(NONE)
 , mVBO(NONE)
 , mCBO(NONE)
{
}

Mesh::~Mesh()
{
	unload();
}

void
Mesh::draw() const
{
	glDrawArrays(
	  mPrimitive,
	  0,
	  size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::load()
{
	assert(mVBO == NONE); // not already loaded

	if (vVertices.size() > 0) { // transfer data
		glGenBuffers(1, &mVBO);
		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(vec3), vVertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), nullptr);
		glEnableVertexAttribArray(0);

		if (vColors.size() > 0) {             // upload colors
			glGenBuffers(1, &mCBO);

			glBindBuffer(GL_ARRAY_BUFFER, mCBO);
			glBufferData(GL_ARRAY_BUFFER, vColors.size() * sizeof(vec4), vColors.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), nullptr);
			glEnableVertexAttribArray(1);
		}
	}
}

void
Mesh::unload()
{
	if (mVAO != NONE) {
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		mVAO = NONE;
		mVBO = NONE;

		if (mCBO != NONE) {
			glDeleteBuffers(1, &mCBO);
			mCBO = NONE;
		}
	}
}

void
Mesh::render() const
{
	assert(mVAO != NONE);

	glBindVertexArray(mVAO);
	draw();
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}
Mesh* Mesh::generateRegularPolygon(GLuint num, GLdouble r) {
	// Se construye sobre el plano Z = 0 así que la z de todos los vértices será igual a 0

	const int centerX = 0;
	const int centerY = 0;

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINE_LOOP;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble angleCount = glm::radians(90.0);
	for (GLuint i = 0; i < num; ++i) {
		GLdouble x = centerX + r * glm::cos(angleCount);
		GLdouble y = centerY + r * glm::sin(angleCount);
		mesh->vVertices.emplace_back(x, y, 0.0);

		angleCount += glm::radians(360.0 / num);
	}
	return mesh;
}

// No lo pone en la práctica pero no sabemos cómo hacerlo sin utilizar un método interno de la clase mesh
Mesh* Mesh::generateTriangleWithColors(GLdouble r) {
	// Se construye sobre el plano Z = 0 así que la z de todos los vértices será igual a 0

	const int centerX = 0;
	const int centerY = 0;

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 3;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);

	GLdouble angleCount = glm::radians(90.0);
	for (GLuint i = 0; i < mesh->mNumVertices; ++i) {
		GLdouble x = centerX + r * glm::cos(angleCount);
		GLdouble y = centerY + r * glm::sin(angleCount);
		mesh->vVertices.emplace_back(x, y, 0.0);
		mesh->vColors.emplace_back(i % 3 == 0, i % 3 == 1, i % 3 == 2, 1);

		angleCount += glm::radians(360.0 / mesh->mNumVertices);
	}

	return mesh;
}
Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h){
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;	

	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);
	
	mesh->vVertices.emplace_back(-(w / 2), (h / 2), 0);
	mesh->vVertices.emplace_back(-w / 2, -(h / 2), 0);
	mesh->vVertices.emplace_back((w / 2), h / 2, 0);
	mesh->vVertices.emplace_back(w / 2, -h / 2, 0);

	return mesh;
}
Mesh* Mesh::generateRGBRectangle(GLdouble w, GLdouble h){
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;	

	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(-(w/2),(h/2),0);
	mesh->vVertices.emplace_back(-w/2,-(h/2),0);
	mesh->vVertices.emplace_back((w/2),h/2,0);
	mesh->vVertices.emplace_back(w/2,-h/2,0);

	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	
	return mesh;
}

Mesh* Mesh::generateCube(GLdouble length) {
	Mesh* mesh = new Mesh();
	GLdouble d = length / 2;

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);

	vec3 v[4] = { {d,-d,d}, {d,-d,-d}, {d,d,-d},{d,d,d} };
	PUSH_TRIANGLE(v[0],v[1],v[2]);
	PUSH_TRIANGLE(v[2],v[3],v[0]);

	vec3 v1[4] = { {d,-d,-d}, {-d,-d,-d}, {-d,d,-d},{d,d,-d} };
	PUSH_TRIANGLE(v1[0], v1[1], v1[2]);
	PUSH_TRIANGLE(v1[2], v1[3], v1[0]);

	vec3 v2[4] = { {-d,-d,-d}, {-d,-d,d}, {-d,d,d},{-d,d,-d} };
	PUSH_TRIANGLE(v2[0], v2[1], v2[2]);
	PUSH_TRIANGLE(v2[2], v2[3], v2[0]);

	vec3 v3[4] = { {-d,-d,d}, {d,-d,d}, {d,d,d},{-d,d,d} };
	PUSH_TRIANGLE(v3[0], v3[1], v3[2]);
	PUSH_TRIANGLE(v3[2], v3[3], v3[0]);

	vec3 v4[4] = { {d,-d,d}, {-d,-d,d}, {-d,-d,-d},{d,-d,-d} };
	PUSH_TRIANGLE(v4[0], v4[1], v4[2]);
	PUSH_TRIANGLE(v4[2], v4[3], v4[0]);

	vec3 v5[4] = { {d,d,d}, {d,d,-d}, {-d,d,-d},{-d,d,d} };
	PUSH_TRIANGLE(v5[0], v5[1], v5[2]);
	PUSH_TRIANGLE(v5[2], v5[3], v5[0]);

	//FIXME: arrglar color cubo wire (es blanco cuando debería ser negro)
	vec4 color = { 0.0,0.0,0.0,1.0 };
	for (int i = 0; i < 36; ++i) {
		mesh->vColors.emplace_back(0.0,0.0,0.0,1.0);
	}

	return mesh;
}

