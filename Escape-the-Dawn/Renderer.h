#ifndef Renderer_h__
#define Renderer_h__

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
#include "ShaderProgram.h"

class Renderer
{
public:
	std::shared_ptr<ShaderProgram> m_ShaderProgram;
	GLuint VAO;

	std::vector<std::vector<float>> Vertices;
	std::vector<std::vector<float>> Normals;
	std::vector<std::vector<float>> TextureCoords;

	Renderer();

	void Draw();
	void DrawText();

	void AddObjectToDraw();
	void AddTextToDraw();

	void LoadContent();

	GLFWwindow* GetWindow() const { return m_Window; }

private:
	GLFWwindow* m_Window;
};

#endif // Renderer_h__