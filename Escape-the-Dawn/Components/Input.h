#ifndef Components_Input_h__
#define Components_Input_h__

#include <array>

#include <GLFW/glfw3.h>

#include "Component.h"

namespace Components
{

struct Input : Component
{
	std::array<int, GLFW_KEY_LAST> KeyState;
	std::array<int, GLFW_KEY_LAST> LastKeyState;
	std::array<int, GLFW_MOUSE_BUTTON_LAST> MouseState;
	std::array<int, GLFW_MOUSE_BUTTON_LAST> LastMouseState;
	float dX, dY;
};

}

#endif // !Components_Input_h__