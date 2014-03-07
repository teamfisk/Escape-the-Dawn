#ifndef InputSystem_h__
#define InputSystem_h__

#include "System.h"
#include "Renderer.h"
#include "Components/Input.h"

namespace Systems
{

class InputSystem : public System
{
public:
	InputSystem(World* world, Renderer* renderer) 
		: System(world), m_Renderer(renderer) {	}

	void Update(double dt, EntityID entity, EntityID parent) override;

private:
	Renderer* m_Renderer;
	float m_LastMouseX, m_LastMouseY;
};

}

#endif // InputSystem_h__
