#ifndef InputSystem_h__
#define InputSystem_h__

#include <array>

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

	void Update(double dt) override;
	void Update(double dt, EntityID entity, EntityID parent) override;

private:
	Renderer* m_Renderer;

	std::array<int, GLFW_KEY_LAST> m_CurrentKeyState;
	std::array<int, GLFW_KEY_LAST> m_LastKeyState;
	std::array<int, GLFW_MOUSE_BUTTON_LAST> m_CurrentMouseState;
	std::array<int, GLFW_MOUSE_BUTTON_LAST> m_LastMouseState;
	float m_CurrentMouseDeltaX, m_CurrentMouseDeltaY;
	float m_LastMouseX, m_LastMouseY;
};

}

#endif // InputSystem_h__
