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
	static GLuint CompileShader(GLenum shaderType, std::string fileName)
	{
		LOG_INFO("Compiling shader \"%s\"", fileName.c_str());

		std::string shaderFile;
		std::ifstream in(fileName, std::ios::in);
		if(!in)
		{
			LOG_ERROR("Error: Failed to open shader file \"%s\"", fileName.c_str());
			return 0;
		}
		in.seekg(0, std::ios::end);
		shaderFile.resize((int)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&shaderFile[0], shaderFile.size());
		in.close();

		GLuint shader = glCreateShader(shaderType);
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
			LOG_ERROR("Shader compilation failed");
			GLsizei infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* infolog = new GLchar[infoLogLength];
			glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, infolog);
			LOG_ERROR(infolog);
			delete[] infolog;
		}

		if(GLERROR("glCompileShader"))
			return 0;

		return shader;
	}

	Shader(GLenum shaderType, std::string fileName)
		: m_ShaderType(shaderType), m_FileName(fileName)
	{
		m_ShaderHandle = 0;
	}

	virtual ~Shader()
	{
		glDeleteShader(m_ShaderHandle);
	}

	GLuint Compile()
	{
		m_ShaderHandle = CompileShader(m_ShaderType, m_FileName);
		return m_ShaderHandle;
	}

	GLenum GetType() const { return m_ShaderType; }
	std::string GetFileName() const { return m_FileName; }
	GLuint GetHandle() const { return m_ShaderHandle; }
	bool IsCompiled() const { return m_ShaderHandle != 0; }

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
	ShaderProgram()
	{
		Initialize();
	}
	
	ShaderProgram(std::string vertexShaderFile, std::string fragmentShaderFile)
	{
		AddShader(std::unique_ptr<Shader>(new VertexShader(vertexShaderFile)));
		AddShader(std::unique_ptr<Shader>(new VertexShader(fragmentShaderFile)));
		Initialize();
	}

	void AddShader(std::unique_ptr<Shader> shader)
	{
		if (!shader->IsCompiled()) {
			shader->Compile();
		}

		m_Shaders.push_back(std::move(shader));
	}

	GLuint Link()
	{
		LOG_INFO("Linking shader program");
		m_ShaderProgramHandle = glCreateProgram();
		for (auto &shader : m_Shaders) {
			glAttachShader(m_ShaderProgramHandle, shader->GetHandle());
		}
		glLinkProgram(m_ShaderProgramHandle);
		if (GLERROR("glLinkProgram"))
			return 0;

		for (auto &shader : m_Shaders) {
			shader.release();
		}
		m_Shaders.clear();
	}

	void Bind()
	{
		if (m_ShaderProgramHandle == 0)
			return;

		glActiveShaderProgram(0, m_ShaderProgramHandle);
	}

	void Unbind()
	{
		glActiveShaderProgram(0, 0);
	}

private:
	GLuint m_ShaderProgramHandle;
	std::vector<std::unique_ptr<Shader>> m_Shaders;
	
	void Initialize()
	{
		m_ShaderProgramHandle = 0;
	}
};

#endif // ShaderProgram_h__