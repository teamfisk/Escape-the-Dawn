#include "ShaderProgram.h"

GLuint Shader::CompileShader(GLenum shaderType, std::string fileName)
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

Shader::Shader(GLenum shaderType, std::string fileName) : m_ShaderType(shaderType), m_FileName(fileName)
{
	m_ShaderHandle = 0;
}

Shader::~Shader()
{
	glDeleteShader(m_ShaderHandle);
}

GLuint Shader::Compile()
{
	m_ShaderHandle = CompileShader(m_ShaderType, m_FileName);
	return m_ShaderHandle;
}

GLenum Shader::GetType() const
{
	return m_ShaderType;
}

std::string Shader::GetFileName() const
{
	return m_FileName;
}

GLuint Shader::GetHandle() const
{
	return m_ShaderHandle;
}

bool Shader::IsCompiled() const
{
	return m_ShaderHandle != 0;
}

ShaderProgram::ShaderProgram()
{
	Initialize();
}

ShaderProgram::ShaderProgram(std::string vertexShaderFile, std::string fragmentShaderFile)
{
	AddShader(std::unique_ptr<Shader>(new VertexShader(vertexShaderFile)));
	AddShader(std::unique_ptr<Shader>(new VertexShader(fragmentShaderFile)));
	Initialize();
}

ShaderProgram::~ShaderProgram()
{
	Unbind();
	glDeleteProgram(m_ShaderProgramHandle);
}

void ShaderProgram::AddShader(std::unique_ptr<Shader> shader)
{
	if (!shader->IsCompiled()) {
		shader->Compile();
	}

	m_Shaders.push_back(std::move(shader));
}

GLuint ShaderProgram::Link()
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

	return m_ShaderProgramHandle;
}

void ShaderProgram::Bind()
{
	if (m_ShaderProgramHandle == 0)
		return;

	glUseProgram(m_ShaderProgramHandle);
}

void ShaderProgram::Unbind()
{
	glActiveShaderProgram(0, 0);
}

void ShaderProgram::Initialize()
{
	m_ShaderProgramHandle = 0;
}
