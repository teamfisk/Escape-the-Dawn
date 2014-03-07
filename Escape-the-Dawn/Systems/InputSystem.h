#ifndef InputSystem_h__
#define InputSystem_h__

#include <GLFW/glfw3.h>

#include "System.h"

#include "Components/Input.h"

namespace Systems
{

class InputSystem : public System
{
public:
	InputSystem(World* world) 
		: System(world) 
	{

	}

	void Update(double dt, EntityID entity, EntityID parent) override;
};

}

#endif // InputSystem_h__
