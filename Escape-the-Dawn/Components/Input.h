#ifndef Components_Input_h__
#define Components_Input_h__

#include "Component.h"
#include <GLFW/glfw3.h>

namespace Components
{

struct Input : Component
{
	int KeyState[GLFW_KEY_LAST];
	int MouseState[GLFW_MOUSE_BUTTON_LAST];
	float dX, dY;
};

}

#endif // !Components_Input_h__