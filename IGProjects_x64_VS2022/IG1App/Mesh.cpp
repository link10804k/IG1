#include "Mesh.h"

using namespace std;
using namespace glm;

// Macro para pushear todos los vértices de un triángulo
#define PUSH_TRIANGLE(V1,V2,V3) mesh->vVertices.emplace_back(V1.x, V1.y,V1.z); \
mesh->vVertices.emplace_back(V2.x, V2.y,V2.z); \
mesh->vVertices.emplace_back(V3.x, V3.y,V3.z) 

// Macro para pushear todos los colores de un cuadrado
#define PUSH_SQUARE_COLOR(color) for (int i = 0; i < 6; ++i){ mesh->vColors.emplace_back(color); }

// Placeholder for the pending index of a GPU object
constexpr GLuint NONE = numeric_limits<GLuint>::max();

Mesh::Mesh()
 : mVAO(NONE)
 , mVBO(NONE)
 , mCBO(NONE)
 , mTCO(NONE)
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

		if (vTexCoords.size() > 0) {
			glGenBuffers(1, &mTCO); // Creamos el buffer de coordenadas de texturas

			glBindBuffer(GL_ARRAY_BUFFER, mTCO); // Bindeamos el buffer reviamente creado de tipo array buffer
			glBufferData(GL_ARRAY_BUFFER, vTexCoords.size() * sizeof(glm::vec2), vTexCoords.data(), GL_STATIC_DRAW); // Crea e inicializa el almacenamiento 
																													 // de datos del buffer
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), nullptr); // Definimos los atributos del buffer 
																						 // (índice, tamaño, tipo, normalización, stride)
			glEnableVertexAttribArray(2); // Activamos el buffer
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

		if (mTCO != NONE) {
			glDeleteBuffers(1, &mTCO);
			mTCO = NONE;
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
	glm::vec4 red = { 1,0,0,1 };
	mesh->vColors.emplace_back(red);
	mesh->vColors.emplace_back(red);
	// Y axis color: green
	glm::vec4 green = { 0,1,0,1 };
	mesh->vColors.emplace_back(green);
	mesh->vColors.emplace_back(green);
	// Z axis color: blue
	glm::vec4 blue = { 0,0,1,1 };
	mesh->vColors.emplace_back(blue);
	mesh->vColors.emplace_back(blue);

	return mesh;
}

// Polígono regular
Mesh* Mesh::generateRegularPolygon(GLuint num, GLdouble r) {
	// Se construye sobre el plano Z = 0 así que la z de todos los vértices será igual a 0

	const int centerX = 0;
	const int centerY = 0;

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINE_LOOP;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble angleCount = glm::radians(90.0);
	// Se colocan los vértices siguiendo una circunferencia
	for (GLuint i = 0; i < num; ++i) {
		GLdouble x = centerX + r * glm::cos(angleCount);
		GLdouble y = centerY + r * glm::sin(angleCount);
		mesh->vVertices.emplace_back(x, y, 0.0);

		angleCount += glm::radians(360.0 / num);
	}
	return mesh;
}

// Triángulo RGB
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
	// Se colocan los vértices siguiendo una circunferencia
	for (GLuint i = 0; i < mesh->mNumVertices; ++i) {
		GLdouble x = centerX + r * glm::cos(angleCount);
		GLdouble y = centerY + r * glm::sin(angleCount);
		mesh->vVertices.emplace_back(x, y, 0.0);

		// Se elige el color según el vértice que sea
		glm::vec4 color = { i % 3 == 0, i % 3 == 1, i % 3 == 2, 1 };

		mesh->vColors.emplace_back(color);

		angleCount += glm::radians(360.0 / mesh->mNumVertices);
	}

	return mesh;
}

// Rectángulo
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

// Rectángulo RGB
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

	glm::vec4 red = { 1,0,0,1 };
	glm::vec4 green = { 0,1,0,1 };
	glm::vec4 blue = { 0,0,1,1 };

	mesh->vColors.emplace_back(red);
	mesh->vColors.emplace_back(green);
	mesh->vColors.emplace_back(green);
	mesh->vColors.emplace_back(blue);
	
	return mesh;
}

// Cubo
Mesh* Mesh::generateCube(GLdouble length) {
	Mesh* mesh = new Mesh();
	GLdouble d = length / 2;

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);

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

	return mesh;
}

// Cubo RGB
Mesh* Mesh::generateRGBCubeTriangles(GLdouble length) {
	Mesh* mesh = new Mesh();
	GLdouble d = length / 2;

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 36;
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);

	glm::vec4 red = { 1,0,0,1 };
	glm::vec4 green = { 0,1,0,1 };
	glm::vec4 blue  = { 0,0,1,1 };

	vec3 v[4] = { {d,-d,d}, {d,-d,-d}, {d,d,-d},{d,d,d} };
	PUSH_TRIANGLE(v[0], v[1], v[2]);
	PUSH_TRIANGLE(v[2], v[3], v[0]);
	PUSH_SQUARE_COLOR(green);

	vec3 v1[4] = { {d,-d,-d}, {-d,-d,-d}, {-d,d,-d},{d,d,-d} };
	PUSH_TRIANGLE(v1[0], v1[1], v1[2]);
	PUSH_TRIANGLE(v1[2], v1[3], v1[0]);
	PUSH_SQUARE_COLOR(red);

	vec3 v2[4] = { {-d,-d,-d}, {-d,-d,d}, {-d,d,d},{-d,d,-d} };
	PUSH_TRIANGLE(v2[0], v2[1], v2[2]);
	PUSH_TRIANGLE(v2[2], v2[3], v2[0]);
	PUSH_SQUARE_COLOR(green);

	vec3 v3[4] = { {-d,-d,d}, {d,-d,d}, {d,d,d},{-d,d,d} };
	PUSH_TRIANGLE(v3[0], v3[1], v3[2]);
	PUSH_TRIANGLE(v3[2], v3[3], v3[0]);
	PUSH_SQUARE_COLOR(red);

	vec3 v4[4] = { {d,-d,d}, {-d,-d,d}, {-d,-d,-d},{d,-d,-d} };
	PUSH_TRIANGLE(v4[0], v4[1], v4[2]);
	PUSH_TRIANGLE(v4[2], v4[3], v4[0]);
	PUSH_SQUARE_COLOR(blue);

	vec3 v5[4] = { {d,d,d}, {d,d,-d}, {-d,d,-d},{-d,d,d} };
	PUSH_TRIANGLE(v5[0], v5[1], v5[2]);
	PUSH_TRIANGLE(v5[2], v5[3], v5[0]);
	PUSH_SQUARE_COLOR(blue);

	return mesh;
}

Mesh* Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
	Mesh* mesh = generateRectangle(w, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);
	mesh->vTexCoords.emplace_back(0.0, rh);
	mesh->vTexCoords.emplace_back(0.0, 0.0);
	mesh->vTexCoords.emplace_back(rw, rh);
	mesh->vTexCoords.emplace_back(rw, 0.0);

	return mesh;
}

Mesh* Mesh::generateBoxOutline(GLdouble length) {
	Mesh* mesh = new Mesh();

	GLdouble l = length / 2;

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);

	//mesh->vVertices.emplace_back(-l, l, l); // 1
	//mesh->vVertices.emplace_back(-l, -l, l); // 2
	//mesh->vVertices.emplace_back(l, l, l); // 3
	//mesh->vVertices.emplace_back(l, -l, l); // 4
	//mesh->vVertices.emplace_back(l, l, -l); // 5
	//mesh->vVertices.emplace_back(l, -l, -l); // 6
	//mesh->vVertices.emplace_back(-l, l, -l); // 7
	//mesh->vVertices.emplace_back(-l, -l, -l); // 8
	//mesh->vVertices.emplace_back(-l, l, l); // 9
	//mesh->vVertices.emplace_back(-l, -l, l); // 10

	mesh->vVertices.emplace_back(l, l, l); // 1
	mesh->vVertices.emplace_back(l, -l, l); // 2
	mesh->vVertices.emplace_back(l, l, -l); // 3
	mesh->vVertices.emplace_back(l, -l, -l); // 4
	mesh->vVertices.emplace_back(-l, l, -l); // 5
	mesh->vVertices.emplace_back(-l, -l, -l); // 6
	mesh->vVertices.emplace_back(-l, l, l); // 7
	mesh->vVertices.emplace_back(-l, -l, l); // 8
	mesh->vVertices.emplace_back(mesh->vVertices[0]); // 9
	mesh->vVertices.emplace_back(mesh->vVertices[1]); // 10

	return mesh;
}

Mesh* Mesh::generateBoxOutlineTexCor(GLdouble length) {
	Mesh* mesh = generateBoxOutline(length);

	mesh->vTexCoords.reserve(mesh->mNumVertices);
	
	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);
	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 1);
	mesh->vTexCoords.emplace_back(1, 0);
	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(0, 0);

	return mesh;
}

Mesh* Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h) { // Radio exterior, número de puntas, z del radio exterior
	Mesh* mesh = new Mesh();

	GLdouble ri = re / 2;

	mesh->mPrimitive = GL_TRIANGLE_FAN;

	// +1 por el vértice central y +1 por el vértice final
	mesh->mNumVertices = np*2 + 2;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// Vértice central
	mesh->vVertices.emplace_back(0, 0, 0);

	GLdouble angleCount = glm::radians(90.0);
	// Se colocan los vértices siguiendo una circunferencia
	for (GLuint i = 0; i < np; ++i) {
		GLdouble x = 0 + re * glm::cos(angleCount);
		GLdouble y = 0 + re * glm::sin(angleCount);
		mesh->vVertices.emplace_back(x, y, h);

		angleCount += glm::radians(360.0 / (np * 2));

		x = 0 + ri * glm::cos(angleCount);
		y = 0 + ri * glm::sin(angleCount);
		mesh->vVertices.emplace_back(x, y, h);

		angleCount += glm::radians(360.0 / (np * 2));
	}

	// Vértice final igual al de la primera punta
	GLdouble x = 0 + re * glm::cos(angleCount);
	GLdouble y = 0 + re * glm::sin(angleCount);
	mesh->vVertices.emplace_back(x, y, h);

	return mesh;
}

Mesh* Mesh::generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h) {
	Mesh* mesh = generateStar3D(re, np, h);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0.5f, 0.5f);

	// TODO: Parametrizar para un número de puntas diferente de 8

	float u = 0;
	float v = 0;
	for (int i = 0; i < 4; ++i) {
		mesh->vTexCoords.emplace_back(u, v);
		u += 0.25f;
	}
	for (int i = 0; i < 4; ++i) {
		mesh->vTexCoords.emplace_back(u, v);
		v += 0.25f;
	}
	for (int i = 0; i < 4; ++i) {
		mesh->vTexCoords.emplace_back(u, v);
		u -= 0.25f;
	}
	for (int i = 0; i < 4; ++i) {
		mesh->vTexCoords.emplace_back(u, v);
		v -= 0.25f;
	}

	mesh->vTexCoords.emplace_back(u, v);

	return mesh;
}

