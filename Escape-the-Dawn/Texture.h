#ifndef Texture_h__
#define Texture_h__

#include <string>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glext.h>
#include <SOIL.h>

class Texture
{
public:
	Texture(std::string path);
	
	~Texture();

	GLuint texture;
	
	void Load(std::string path);
	void Bind();
};

#endif // Texture_h__
