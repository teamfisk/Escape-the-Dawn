#ifndef Skybox_h__
#define Skybox_h__

#include <algorithm>

#include "OpenGL.h"
#include "logging.h"
#include "glerror.h"
#include "CubemapTexture.h"

class Skybox
{
public:
	Skybox(CubemapTexture cubemap);
	~Skybox();

	void Draw();

private:
	CubemapTexture m_Cubemap;

	GLuint ibo;
	GLuint vao;

	float m_CubeVertices[3 * 8];
	int m_CubeIndices[1];
};

#endif // Skybox_h__