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
	WIDTH = 1280;
	HEIGHT = 720;
	m_Window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", nullptr, nullptr);
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

	// Create Camera

	m_Camera = std::make_shared<Camera>(45.f, (float)WIDTH / HEIGHT, 0.01f, 1000.f);
	m_Camera->Position(glm::vec3(0.0f, 0.0f, 2.f));

	LoadContent();
}

void Renderer::Draw(double _dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

	m_ShaderProgram.Bind();

	glm::mat4 cameraMatrix = m_Camera->ProjectionMatrix() * m_Camera->ViewMatrix();

	glm::mat4 MVP;
	for(int i = 0; i < ModelsToRender.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ModelsToRender[i]->model->texture[0]->texture); 
		MVP = cameraMatrix * ModelsToRender[i]->ModelMatrix;
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "model"), 1, GL_FALSE, glm::value_ptr(ModelsToRender[i]->ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "view"), 1, GL_FALSE, glm::value_ptr(m_Camera->ViewMatrix()));
		glUniform3fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "position"), 2, Light_position.data());
		glUniform3fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "specular"), 2, Light_specular.data());
		glUniform3fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "diffuse"), 2, Light_diffuse.data());
		glUniform1fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "constantAttenuation"), 2, Light_constantAttenuation.data());
		glUniform1fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "linearAttenuation"), 2, Light_linearAttenuation.data());
		glUniform1fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "quadraticAttenuation"), 2, Light_quadraticAttenuation.data());
		glUniform1fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "spotExponent"), 2, Light_spotExponent.data());
		glBindVertexArray(ModelsToRender[i]->model->VAO);
		glDrawArrays(GL_TRIANGLES, 0, ModelsToRender[i]->model->Vertices.size());

	}
	ModelsToRender.clear();

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

void Renderer::AddModelToDraw(Model* _model, glm::vec3 _position, glm::quat _orientation)
{
	glm::mat4 RotationMatrix = glm::toMat4(_orientation);
	glm::mat4 ModelMatrix = glm::translate(glm::mat4(), _position) * RotationMatrix ;
	// You can now use ModelMatrix to build the MVP matrix
	ModelsToRender.push_back(new ModelData(_model, ModelMatrix));
}

void Renderer::AddPointLightToDraw(
	glm::vec3 _position,
	glm::vec3 _specular, 
	glm::vec3 _diffuse, 
	float _constantAttenuation, 
	float _linearAttenuation, 
	float _quadraticAttenuation, 
	float _spotExponent
	)
{
	Light_position.push_back(_position.x);
	Light_position.push_back(_position.y);
	Light_position.push_back(_position.z);
	Light_specular.push_back(_specular.x);
	Light_specular.push_back(_specular.y);
	Light_specular.push_back(_specular.z);
	Light_diffuse.push_back(_diffuse.x);
	Light_diffuse.push_back(_diffuse.y);
	Light_diffuse.push_back(_diffuse.z);
	Light_constantAttenuation.push_back(_constantAttenuation);
	Light_linearAttenuation.push_back(_linearAttenuation);
	Light_quadraticAttenuation.push_back(_quadraticAttenuation);
	Light_spotExponent.push_back(_spotExponent);

}


void Renderer::LoadContent()
{
	m_ShaderProgram.AddShader(std::unique_ptr<Shader>(new VertexShader("Shaders/Vertex.glsl")));
	m_ShaderProgram.AddShader(std::unique_ptr<Shader>(new FragmentShader("Shaders/Fragment.glsl")));
	m_ShaderProgram.Compile();
	m_ShaderProgram.Link();
}
