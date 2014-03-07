#include "InputSystem.h"
#include "World.h"

void Systems::InputSystem::Update(double dt, EntityID entity, EntityID parent)
{
	auto input = m_World->GetComponent<Components::Input>(entity, "Input");
	if (input == nullptr)
		return;


}

