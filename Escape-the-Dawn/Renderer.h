#ifndef Renderer_h__
#define Renderer_h__

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "OpenGL.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "glerror.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "Model.h"

class Renderer
{
public:
	
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	int HEIGHT, WIDTH;

	struct ModelData
	{
		std::shared_ptr<Model> model;
		glm::mat4 ModelMatrix;
		ModelData(std::shared_ptr<Model> _model, glm::mat4 _modelMatrix) 
			: model(_model), ModelMatrix(_modelMatrix) {}
	};

	std::vector<ModelData*> ModelsToRender;

	Renderer();

	void Initialize();
	void Draw(double dt);
	void DrawText();

	void AddModelToDraw(std::shared_ptr<Model> model, glm::vec3 position, glm::quat orientation);
	void AddTextToDraw();

	void LoadContent();

	GLFWwindow* GetWindow() const { return m_Window; }
	std::shared_ptr<Camera> GetCamera() const { return m_Camera; }

	bool DrawNormals() const { return m_DrawNormals; }
	void DrawNormals(bool val) { m_DrawNormals = val; }
	bool DrawWireframe() const { return m_DrawWireframe; }
	void DrawWireframe(bool val) { m_DrawWireframe = val; }

private:
	GLFWwindow* m_Window;
	GLint m_glVersion[2];
	GLchar* m_glVendor;
	bool m_VSync;
	bool m_DrawNormals;
	bool m_DrawWireframe;

	std::shared_ptr<Camera> m_Camera;

	ShaderProgram m_ShaderProgram;
	ShaderProgram m_ShaderProgramNormals;

	void DrawModels();

};

#endif // Renderer_h__