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
		glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
		glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
		glVendor = (GLchar*)glGetString(GL_VENDOR);
		std::stringstream ss;
		ss << glVendor << " OpenGL " << glVersion[0] << "." << glVersion[1];
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
	}

	bool Running() const { return !glfwWindowShouldClose(m_Window); }

	void Tick()
	{
		glfwPollEvents();
	}

private:
	GLFWwindow* m_Window;
	GLint glVersion[2];
	GLchar* glVendor;
};