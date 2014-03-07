#ifndef ShaderProgram_h__
#define ShaderProgram_h__

#include <memory>
#include <string>
#include <fstream>
#include <vector>

#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glext.h>

#include "glerror.h"

class Shader
{
public:
	static GLuint CompileShader(GLenum shaderType, std::string fileName);

	Shader(GLenum shaderType, std::string fileName);

	virtual ~Shader();

	GLuint Compile();

	GLenum GetType() const;
	std::string GetFileName() const;
	GLuint GetHandle() const;
	bool IsCompiled() const;

protected:
	GLenum m_ShaderType;
	std::string m_FileName;
	GLint m_ShaderHandle;
};

template <int SHADERTYPE>
class ShaderType : public Shader
{
public:
	ShaderType(std::string fileName) 
		: Shader(SHADERTYPE, fileName) { }
};

class VertexShader : public ShaderType<GL_VERTEX_SHADER>
{
public:
	VertexShader(std::string fileName)
		: ShaderType(fileName) { }
};

class FragmentShader : public ShaderType<GL_FRAGMENT_SHADER>
{
public:
	FragmentShader(std::string fileName)
		: ShaderType(fileName) { }
};

class GeometryShader : public ShaderType<GL_GEOMETRY_SHADER>
{
public:
	GeometryShader(std::string fileName)
		: ShaderType(fileName) { }
};

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	
	void AddShader(std::unique_ptr<Shader> shader);

	void Compile();
	GLuint Link();

	void Bind();

	void Unbind();

private:
	GLuint m_ShaderProgramHandle;
	std::vector<std::unique_ptr<Shader>> m_Shaders;
	
	void Initialize();
};

#endif // ShaderProgram_h__