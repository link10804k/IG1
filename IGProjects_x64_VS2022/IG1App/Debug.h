#ifndef DEBUG_H
#define DEBUG_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

class Debug {
public:
	static void printMatrix(const glm::mat4& mat) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				printf(std::to_string(mat[i][j]).c_str());
				printf(" ");
			}
			printf("\n");
		}
	}
};

#endif
