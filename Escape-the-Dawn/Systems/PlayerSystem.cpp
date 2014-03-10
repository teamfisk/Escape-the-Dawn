#include "PlayerSystem.h"
#include "World.h"



void Systems::PlayerSystem::Update(double dt)
{

}

void Systems::PlayerSystem::UpdateEntity(double dt, EntityID entity, EntityID parent)
{
	auto transform = m_World->GetComponent<Components::Transform>(entity, "Transform");
	if (transform == nullptr)
		return;
	auto input = m_World->GetComponent<Components::Input>(entity, "Input");
	if (input == nullptr)
		return;

	auto name = m_World->GetProperty<std::string>(entity, "Name");
	if (name == "Camera") {

		glm::vec3 Camera_Right = glm::rotate(transform->Orientation, glm::vec3(1, 0, 0));
		glm::vec3 Camera_Forward = glm::rotate(transform->Orientation, glm::vec3(0, 0, 1));


		float speed = 4.0f;
		if(input->KeyState[GLFW_KEY_LEFT_SHIFT] == GLFW_PRESS)
		{
			speed = 1.0f;
		}
		if(input->KeyState[GLFW_KEY_A] == GLFW_PRESS)
		{
			transform->Position -= Camera_Right * (float)dt*2.f * speed;
		}
		if(input->KeyState[GLFW_KEY_D] == GLFW_PRESS)
		{
			transform->Position += Camera_Right * (float)dt*2.f * speed;
		}
		if(input->KeyState[GLFW_KEY_W] == GLFW_PRESS)
		{
			transform->Position -= Camera_Forward * (float)dt*2.f * speed;
		}
		if(input->KeyState[GLFW_KEY_S] == GLFW_PRESS)
		{
			transform->Position += Camera_Forward * (float)dt*2.f * speed;
		}

		transform->Orientation = transform->Orientation * glm::angleAxis<float>(-(input->dX/300.f),glm::vec3(0,1,0));
		transform->Orientation = transform->Orientation * glm::angleAxis<float>(-(input->dY/300.f),glm::vec3(1,0,0));
	}
}
