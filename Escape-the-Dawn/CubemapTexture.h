#ifndef CubemapTexture_h__
#define CubemapTexture_h__

#include "OpenGL.h"
#include "glerror.h"
#include <SOIL.h>

#include "logging.h"

class CubemapTexture
{
public:
	CubemapTexture() { }
	CubemapTexture(
		char* posXFile,
		char* negXFile,
		char* posYFile,
		char* negYFile,
		char* posZFile,
		char* negZFile);
	~CubemapTexture();

	void Load();
	void Bind(GLenum textureSlot);

private:
	char* m_TextureFiles[6];
	GLuint m_Texture;
};

#endif // CubemapTexture_h__