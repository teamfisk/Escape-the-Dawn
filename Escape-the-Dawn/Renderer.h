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


class Renderer
{
public:
	GLuint shaderProgram;
	GLuint VAO;

	Renderer();

	std::vector<std::vector<float>> Vertices;
	std::vector<std::vector<float>> Normals;
	std::vector<std::vector<float>> TextureCoords;

	void PushVertices(std::vector<float>);
	void PushNormals(std::vector<float>);
	void PushTextureCoords(std::vector<float>);
	GLuint CompileShader(GLenum, std::string);

};