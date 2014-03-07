#ifndef Model_h__
#define Model_h__

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

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

#include "Texture.h"

class Model
{
public:
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec3> Normals;
	std::vector<glm::vec2> TextureCoords;

	GLuint VertexBuffer;
	GLuint NormalBuffer;
	GLuint TextureCoordBuffer;
	GLuint VAO;

	std::vector<std::shared_ptr<Texture>> texture;

	Model(const char* path);

	bool Loadobj(
		const char* path, 
		std::vector <glm::vec3> & out_vertices, 
		std::vector <glm::vec3> &out_normals, 
		std::vector <glm::vec2> & out_TextureCoords
		);
	
	void CreateBuffers(
		std::vector<glm::vec3> _Vertices, 
		std::vector<glm::vec3> _Normals, 
		std::vector<glm::vec2>_TextureCoords
		);

};
#endif // Model_h__