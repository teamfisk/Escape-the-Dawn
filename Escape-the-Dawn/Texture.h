#ifndef Texture_h__
#define Texture_h__

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glext.h>
#include <SOIL.h>

//#include "Renderer.h"

class Texture
{
public:
	Texture(const char* path);
	
	~Texture();

	GLuint texture;
	
	void Load(const char* path);
	void Bind();
};

#endif // Texture_h__
