#include "Renderer.h"

Renderer::Renderer()
{
	glEnable(GL_DEPTH_TEST);
}

void Renderer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

	m_ShaderProgram->Bind();
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

void Renderer::LoadContent()
{
	m_ShaderProgram->AddShader(std::unique_ptr<Shader>(new VertexShader("Shaders/Vertex.glsl")));
	m_ShaderProgram->AddShader(std::unique_ptr<Shader>(new FragmentShader("Shaders/Fragment.glsl")));
	m_ShaderProgram->Link();
}
