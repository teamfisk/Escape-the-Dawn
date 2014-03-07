#include <string>
#include <sstream>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glext.h>

#include "logging.h"
#include "glerror.h"

#include "World.h"



class Engine
{
public:
	Engine(int argc, char* argv[])
	{
		renderer.Initialize();
		m_LastTime = glfwGetTime();
	}

	bool Running() const { return !glfwWindowShouldClose(renderer.GetWindow()); }

	void Tick()
	{
		double currentTime = glfwGetTime();
		double dt =  currentTime - m_LastTime;
		m_LastTime = currentTime;

		//World.Update(dt);
		renderer.Draw(dt);

		glfwPollEvents();
	}

private:
	Renderer renderer;
	double m_LastTime;
};