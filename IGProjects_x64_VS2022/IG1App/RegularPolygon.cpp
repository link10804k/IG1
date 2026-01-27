#include "RegularPolygon.h"

RegularPolygon::RegularPolygon(GLuint num, GLdouble r, glm::vec4 mColor) : SingleColorEntity(mColor) {
	mMesh = Mesh::generateRegularPolygon(num, r);
}