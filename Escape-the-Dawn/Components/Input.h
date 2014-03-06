#ifndef Input_h__
#define Input_h__

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
	REGISTER_COMPONENT("Input", Input);

}
#endif // !Input_h__