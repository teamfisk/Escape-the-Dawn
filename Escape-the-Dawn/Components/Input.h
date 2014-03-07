#ifndef Components_Input_h__
#define Components_Input_h__

#include "Component.h"
#include <GLFW/glfw3.h>

namespace Components
{

struct Input : Component
{
	int KeyState[GLFW_KEY_LAST];
	float MouseState[2];
	float dX, dY;
};

}

#endif // !Components_Input_h__