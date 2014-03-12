#include "Renderer.h"

Renderer::Renderer()
{
	m_VSync = false;
	m_DrawNormals = false;
	m_DrawWireframe = false;

	m_SunPosition = glm::vec3(0, 10, 10);
	m_SunTarget = glm::vec3(0, 0, 0);
	m_SunProjection = glm::ortho<float>(-20, 20, -20, 20, -10, 20);
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
	
	// Create Camera
	m_Camera = std::make_shared<Camera>(45.f, (float)WIDTH / HEIGHT, 0.01f, 1000.f);
	m_Camera->Position(glm::vec3(0.0f, 0.0f, 2.f));

	glfwSwapInterval(m_VSync);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	LoadContent();
}

void Renderer::LoadContent()
{
	auto standardVS = std::shared_ptr<Shader>(new VertexShader("Shaders/Vertex.glsl"));
	auto standardFS = std::shared_ptr<Shader>(new FragmentShader("Shaders/Fragment.glsl"));

	m_ShaderProgram.AddShader(standardVS);
	m_ShaderProgram.AddShader(standardFS);
	m_ShaderProgram.Compile();
	m_ShaderProgram.Link();

	m_ShaderProgramNormals.AddShader(std::shared_ptr<Shader>(new GeometryShader("Shaders/Normals.geo.glsl")));
	m_ShaderProgramNormals.AddShader(standardVS);
	m_ShaderProgramNormals.AddShader(std::shared_ptr<Shader>(new FragmentShader("Shaders/Normals.frag.glsl")));
	m_ShaderProgramNormals.Compile();
	m_ShaderProgramNormals.Link();

	m_ShaderProgramShadows.AddShader(std::shared_ptr<Shader>(new VertexShader("Shaders/ShadowMap.vert.glsl")));
	m_ShaderProgramShadows.AddShader(std::shared_ptr<Shader>(new FragmentShader("Shaders/ShadowMap.frag.glsl")));
	m_ShaderProgramShadows.Compile();
	m_ShaderProgramShadows.Link();

	m_ShaderProgramShadowsDrawDepth.AddShader(std::shared_ptr<Shader>(new VertexShader("Shaders/VisualizeDepth.vert.glsl")));
	m_ShaderProgramShadowsDrawDepth.AddShader(std::shared_ptr<Shader>(new FragmentShader("Shaders/VisualizeDepth.frag.glsl")));
	m_ShaderProgramShadowsDrawDepth.Compile();
	m_ShaderProgramShadowsDrawDepth.Link();

	m_ShaderProgramDebugAABB.AddShader(standardVS);
	m_ShaderProgramDebugAABB.AddShader(std::shared_ptr<Shader>(new FragmentShader("Shaders/AABB.frag.glsl")));
	m_ShaderProgramDebugAABB.Compile();
	m_ShaderProgramDebugAABB.Link();

	m_DebugAABB = CreateAABB();
	m_ScreenQuad = CreateQuad();
	CreateShadowMap(2048*2);
}

void Renderer::CreateShadowMap(int resolution)
{
	glGenFramebuffers(1, &m_ShadowFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowFrameBuffer);

	// Depth texture
	glGenTextures(1, &m_ShadowDepthTexture);
	glBindTexture(GL_TEXTURE_2D, m_ShadowDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE );
	//glTexParameteri( GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY );

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_ShadowDepthTexture, 0);
	glDrawBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		LOG_ERROR("Framebuffer incomplete!");
		return;
	}
}
void Renderer::Draw(double dt)
{
	glDisable(GL_BLEND);

	DrawShadowMap();
	DrawScene();

#ifdef DEBUG
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
	m_ShaderProgramDebugAABB.Bind();
	for (auto aabbModelMatrix : AABBsToRender) {
		glm::mat4 cameraMatrix = m_Camera->ProjectionMatrix() * m_Camera->ViewMatrix();
		glm::mat4 MVP = cameraMatrix * aabbModelMatrix;
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgramDebugAABB.GetHandle(), "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
		glBindVertexArray(m_DebugAABB);
		glDrawArrays(GL_LINES, 0, 24);
	}
	AABBsToRender.clear();
#endif

	DrawDebugShadowMap();

	ModelsToRender.clear();
	glfwSwapBuffers(m_Window);
}

void Renderer::DrawScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, WIDTH, HEIGHT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
#ifdef DEBUG
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_BACK, GL_LINE);
#endif

	// Draw models
	glm::mat4 depthViewMatrix = glm::lookAt(m_SunPosition, m_SunTarget, glm::vec3(0, 1, 0));
	glm::mat4 depthCamera = m_SunProjection * depthViewMatrix;
	glm::mat4 depthMVP = depthCamera;
	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);
	glm::mat4 depthBiasMVP = biasMatrix * depthMVP;

	m_ShaderProgram.Bind();
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "DepthMVP"), 1, GL_FALSE, glm::value_ptr(depthBiasMVP));
	glUniform3fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "position"), 3, Light_position.data());
	glUniform3fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "specular"), 3, Light_specular.data());
	glUniform3fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "diffuse"), 3, Light_diffuse.data());
	glUniform1fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "constantAttenuation"), 3, Light_constantAttenuation.data());
	glUniform1fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "linearAttenuation"), 3, Light_linearAttenuation.data());
	glUniform1fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "quadraticAttenuation"), 3, Light_quadraticAttenuation.data());
	glUniform1fv(glGetUniformLocation(m_ShaderProgram.GetHandle(), "spotExponent"), 3, Light_spotExponent.data());
	if (m_DrawWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_ShadowDepthTexture);
	DrawModels(m_ShaderProgram);

#ifdef DEBUG
	// Debug draw model normals
	if (m_DrawNormals) {
		m_ShaderProgramNormals.Bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		DrawModels(m_ShaderProgramNormals);
	}
#endif
}

void Renderer::DrawShadowMap()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glBindFramebuffer(GL_FRAMEBUFFER, m_ShadowFrameBuffer);
	glViewport(0, 0, 2048*2, 2048*2);

	glClear(GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glm::mat4 depthViewMatrix = glm::lookAt(m_SunPosition, m_SunTarget, glm::vec3(0, 1, 0));
	glm::mat4 depthCamera = m_SunProjection * depthViewMatrix;

	//glm::mat4 cameraMatrix = depthProjectionMatrix * m_Camera->ViewMatrix();

	glm::mat4 MVP;

	m_ShaderProgramShadows.Bind();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int i = 0; i < ModelsToRender.size(); i++)
	{
		ModelData* modelData = ModelsToRender.at(i);
		auto model = modelData->model;

		MVP = depthCamera * modelData->ModelMatrix;
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgramShadows.GetHandle(), "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

		glBindVertexArray(model->VAO);
		for (auto texGroup : model->TextureGroups) {
			glDrawArrays(GL_TRIANGLES, texGroup.StartIndex, texGroup.EndIndex - texGroup.StartIndex + 1);
		}
	}
}

void Renderer::DrawDebugShadowMap()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 200*(16.f/9.f), 200);

	glClear(GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	m_ShaderProgramShadowsDrawDepth.Bind();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ShadowDepthTexture);
	glBindVertexArray(m_ScreenQuad);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::DrawModels(ShaderProgram &shader)
{
	glm::mat4 cameraMatrix = m_Camera->ProjectionMatrix() * m_Camera->ViewMatrix();

	glm::mat4 MVP;
	for (int i = 0; i < ModelsToRender.size(); i++)
	{
		ModelData* modelData = ModelsToRender.at(i);
		auto model = modelData->model;

		MVP = cameraMatrix * modelData->ModelMatrix;
		glUniformMatrix4fv(glGetUniformLocation(shader.GetHandle(), "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));
		glUniformMatrix4fv(glGetUniformLocation(shader.GetHandle(), "model"), 1, GL_FALSE, glm::value_ptr(modelData->ModelMatrix));
		glUniformMatrix4fv(glGetUniformLocation(shader.GetHandle(), "view"), 1, GL_FALSE, glm::value_ptr(m_Camera->ViewMatrix()));
		glBindVertexArray(model->VAO);
		for (auto texGroup : model->TextureGroups) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texGroup.Texture->texture); 
			glDrawArrays(GL_TRIANGLES, texGroup.StartIndex, texGroup.EndIndex - texGroup.StartIndex + 1);
		}
	}
}

void Renderer::DrawText()
{
	//DrawShitInTextForm
}

void Renderer::AddTextToDraw()
{
	//Add to draw shit vector
}

void Renderer::AddModelToDraw(std::shared_ptr<Model> _model, glm::vec3 _position, glm::quat _orientation)
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

GLuint Renderer::CreateQuad()
{
	float quadVertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,

		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};
	float quadTexCoords[] = {
		0.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};
	GLuint vbo[2], vao;
	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(float), quadVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 6 * sizeof(float), quadTexCoords, GL_STATIC_DRAW);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vao;
}

GLuint Renderer::CreateAABB()
{
	float vertices[] = {
		// Bottom
		-1.0f, -1.0f, 1.0f, // 0
		1.0f, -1.0f, 1.0f, // 1
		1.0f, -1.0f, 1.0f, // 1
		1.0f, -1.0f, -1.0f, // 2
		1.0f, -1.0f, -1.0f, // 2
		-1.0f, -1.0f, -1.0f, // 3
		-1.0f, -1.0f, -1.0f, // 3
		-1.0f, -1.0f, 1.0f, // 0

		// Top
		-1.0f, 1.0f, 1.0f, // 4
		1.0f, 1.0f, 1.0f, // 5
		1.0f, 1.0f, 1.0f, // 5
		1.0f, 1.0f, -1.0f, // 6
		1.0f, 1.0f, -1.0f, // 6
		-1.0f, 1.0f, -1.0f, // 7
		-1.0f, 1.0f, -1.0f, // 7
		-1.0f, 1.0f, 1.0f, // 4

		// Connectors
		-1.0f, -1.0f, 1.0f, // 0
		-1.0f, 1.0f, 1.0f, // 4
		1.0f, -1.0f, 1.0f, // 1
		1.0f, 1.0f, 1.0f, // 5
		1.0f, -1.0f, -1.0f, // 2
		1.0f, 1.0f, -1.0f, // 6
		-1.0f, -1.0f, -1.0f, // 3
		-1.0f, 1.0f, -1.0f, // 7
	};

	GLuint vbo, vao;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vao;
}

void Renderer::AddAABBToDraw(glm::vec3 origin, glm::vec3 volumeVector)
{
	glm::mat4 model;
	model *= glm::translate(origin);
	model *= glm::scale(volumeVector);
	AABBsToRender.push_back(model);
}
