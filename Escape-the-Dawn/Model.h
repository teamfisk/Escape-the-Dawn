#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glext.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glerror.h"
#include <cstdlib>

class Model
{
public:
	glm::vec3 Position;
	std::vector<float> Colors;
	std::vector<float> Vertices;
	std::vector<float> Normals;
	std::vector<float> TextureCoords;

	GLuint Colorbuffer;
	GLuint VertBuffer;
	GLuint NormalBuffer;
	GLuint TextureCoordBuffer;
	GLuint VAO;

	Model();

	void temp_CreateModelShit();
	void CreateBuffers(std::vector<float>, std::vector<float>, std::vector<float>);

};