#include "CubemapTexture.h"

CubemapTexture::CubemapTexture(char* posXFile, char* negXFile, char* posYFile, char* negYFile, char* posZFile, char* negZFile)
{
	m_TextureFiles[0] = posXFile;
	m_TextureFiles[1] = negXFile;
	m_TextureFiles[2] = posYFile;
	m_TextureFiles[3] = negYFile;
	m_TextureFiles[4] = posZFile;
	m_TextureFiles[5] = negZFile;

	Load();
}

CubemapTexture::~CubemapTexture()
{
	//glDeleteTextures(1, &m_Texture);
}

void CubemapTexture::Load()
{
	m_Texture = SOIL_load_OGL_cubemap(
		m_TextureFiles[0], 
		m_TextureFiles[1],
		m_TextureFiles[2],
		m_TextureFiles[3],
		m_TextureFiles[4],
		m_TextureFiles[5],
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		0);

	if (m_Texture == 0)
		LOG_ERROR("SOIL cubemap loading error: %s", SOIL_last_result());

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubemapTexture::Bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
}
