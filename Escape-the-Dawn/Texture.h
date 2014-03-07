#include <SOIL.h>
#include "Renderer.h"


class Texture
{
public:
	
	Texture(const char* path);
	
	~Texture();

	GLuint texture;
	
	void Load(const char* path);
	void Bind();
};
