#include "Texture.h"

Texture::Texture( const char* path )
{
	Load(path);
}


void Texture::Load( const char* path )
{
	texture = SOIL_load_OGL_texture(path, 0, 0, SOIL_FLAG_INVERT_Y);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}


