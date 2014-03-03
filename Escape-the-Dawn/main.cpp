#include <string>
#include <sstream>

#include <GL/glew.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <glext.h>

#include "logging.h"
#include "glerror.h"

#include "World.h"

GLFWwindow* window;
GLint glVersion[2];
GLchar* glVendor;

int main(int argc, char* argv[])
{
	World world;

	EntityID ent1 = world.CreateEntity();
	auto t1 = world.AddComponent<Components::Transform>(ent1, "Transform");
	t1->Position[0] = 1.0f;
	t1->Position[1] = 1.0f;
	t1->Position[2] = 1.0f;
	EntityID ent2 = world.CreateEntity(ent1);
	auto t2 = world.AddComponent<Components::Transform>(ent2, "Transform");
	t2->Position[0] = 1.0f;
	t2->Position[1] = 1.0f;
	t2->Position[2] = 1.0f;

	world.Update(0.0);

	LOG_INFO("ent1: %f %f %f", t1->Position[0], t1->Position[1], t1->Position[2]);
	LOG_INFO("ent2: %f %f %f", t2->Position[0], t2->Position[1], t2->Position[2]);

	return 0;

	// Initialize GLFW
	if (!glfwInit())
	{
		LOG_ERROR("GLFW: Initialization failed");
		return 1;
	}

	// Create a window
	window = glfwCreateWindow(1280, 720, "OpenGL", nullptr, nullptr);
	if (!window)
	{
		LOG_ERROR("GLFW: Failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);

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
	glfwSetWindowTitle(window, ss.str().c_str());

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		LOG_ERROR("GLEW: Initialization failed");
		return 1;
	}

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}

	return 0;
}