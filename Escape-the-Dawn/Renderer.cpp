#include "Renderer.h"

Renderer::Renderer()
{
}

void Renderer::Initialize()
{
	// Initialize GLFW
	if (!glfwInit()) {
		LOG_ERROR("GLFW: Initialization failed");
		exit(EXIT_FAILURE);
	}

	// Create a window
	m_Window = glfwCreateWindow(1280, 720, "OpenGL", nullptr, nullptr);
	if (!m_Window) {
		LOG_ERROR("GLFW: Failed to create window");
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_Window);

	// GL version info
	glGetIntegerv(GL_MAJOR_VERSION, &m_glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &m_glVersion[1]);
	m_glVendor = (GLchar*)glGetString(GL_VENDOR);
	std::stringstream ss;
	ss << m_glVendor << " OpenGL " << m_glVersion[0] << "." << m_glVersion[1];
#ifdef DEBUG
	ss << " DEBUG";
#endif
	LOG_INFO(ss.str().c_str());
	glfwSetWindowTitle(m_Window, ss.str().c_str());

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		LOG_ERROR("GLEW: Initialization failed");
		exit(EXIT_FAILURE);
	}
	glEnable(GL_DEPTH_TEST);

	LoadContent();
}

void Renderer::Draw(double _dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

	//m_ShaderProgram->Bind();

	glfwSwapBuffers(m_Window);
}

void Renderer::DrawText()
{
	//DrawShitInTextForm
}

void Renderer::AddTextToDraw()
{
	//Add to draw shit vector
}

void Renderer::AddModelToDraw(Model* _model)
{
	ModelsToRender.push_back(_model);
}

//Fixa med shaders, lägga in alla verts osv.

void Renderer::LoadContent()
{
	m_ShaderProgram->AddShader(std::unique_ptr<Shader>(new VertexShader("Shaders/Vertex.glsl")));
	m_ShaderProgram->AddShader(std::unique_ptr<Shader>(new FragmentShader("Shaders/Fragment.glsl")));
	m_ShaderProgram->Link();
}
