#include "Renderer.h"

Renderer::Renderer()
{

}

void Renderer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

	glUseProgram(shaderProgram);
}

void Renderer::DrawText()
{
	//DrawShitInTextForm
}

void Renderer::AddTextToDraw()
{
	//Add to draw shit vector
}

void Renderer::AddObjectToDraw()
{

}

//Fixa med shaders, lägga in alla verts osv.


GLuint Renderer::CompileShader(GLenum shaderType, std::string fileName)
{
	std::string shaderFile;
	std::ifstream in(fileName, std::ios::in);

	if(!in)
	{
		LOG_ERROR("Error: Failed to open shader file %s", fileName);
		return 0;
	}
	in.seekg(0, std::ios::end);
	shaderFile.resize((int)in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&shaderFile[0], shaderFile.size());
	in.close();

	GLuint shader = glCreateShader(shaderType); //GL_VERTEX_SHADER, GL_FRAGMENT_SHADER
	if(GLERROR("glCreateShader"))
		return 0;

	const GLchar* shaderFiles = shaderFile.c_str();
	const GLint length = shaderFile.length();
	glShaderSource(shader, 1, &shaderFiles, &length);
	if(GLERROR("glShaderSource"))
		return 0;

	glCompileShader(shader);
	GLint compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if(compileStatus != GL_TRUE)
	{
		GLsizei infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infolog = new GLchar[infoLogLength];
		glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infolog);
		std::cerr << infolog << std::endl;
		delete[] infolog;
	}

	if(GLERROR("glCompileShader"))
		return 0;

	return shader;

}

