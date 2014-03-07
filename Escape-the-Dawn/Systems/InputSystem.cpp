#include "InputSystem.h"
#include "World.h"

void Systems::InputSystem::Update(double dt)
{
	m_LastKeyState = m_CurrentKeyState;
	m_LastMouseState = m_CurrentMouseState;

	// Keyboard input
	for (int i = 0; i <= GLFW_KEY_LAST; ++i) {
		m_CurrentKeyState[i] = glfwGetKey(m_Renderer->GetWindow(), i);
	}

	// Mouse buttons
	for (int i = 0; i <= GLFW_MOUSE_BUTTON_LAST; ++i) {
		m_CurrentKeyState[i] = glfwGetMouseButton(m_Renderer->GetWindow(), i);
	}

	// Cursor position
	double xpos, ypos;
	glfwGetCursorPos(m_Renderer->GetWindow(), &xpos, &ypos);
	m_CurrentMouseDeltaX = xpos - m_LastMouseX;
	m_CurrentMouseDeltaY = ypos - m_LastMouseY;
	m_LastMouseX = xpos;
	m_LastMouseY = ypos;
}

void Systems::InputSystem::Update(double dt, EntityID entity, EntityID parent)
{
	auto input = m_World->GetComponent<Components::Input>(entity, "Input");
	if (input == nullptr)
		return;

	input->KeyState = m_CurrentKeyState;
	input->LastKeyState = m_LastKeyState;
	input->MouseState = m_CurrentMouseState;
	input->LastMouseState = m_LastMouseState;
	input->dX = m_CurrentMouseDeltaX;
	input->dY = m_CurrentMouseDeltaY;
}
