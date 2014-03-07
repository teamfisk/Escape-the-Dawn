#include "InputSystem.h"
#include "World.h"

void Systems::InputSystem::Update(double dt, EntityID entity, EntityID parent)
{
	auto input = m_World->GetComponent<Components::Input>(entity, "Input");
	if (input == nullptr)
		return;

	for (int i = 0; i <= GLFW_KEY_LAST; ++i) {
		input->KeyState[i] = glfwGetKey(m_Renderer->GetWindow(), i);
	}

	for (int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; ++i) {
		input->MouseState[i] = glfwGetMouseButton(m_Renderer->GetWindow(), i);
	}
}

