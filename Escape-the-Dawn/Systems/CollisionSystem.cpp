#include "CollisionSystem.h"
#include "World.h"

void Systems::Collision::Update(double dt, EntityID entity, EntityID parent)
{
	if (parent != 0)
	{
		auto transform = m_World->GetComponent<Components::Transform>(entity, "Transform");
		auto parentTransform = m_World->GetComponent<Components::Transform>(parent, "Transform");

		transform->Position[0] += parentTransform->Position[0];
		transform->Position[1] += parentTransform->Position[1];
		transform->Position[2] += parentTransform->Position[2];
	}
	LOG_INFO("Updating entity %i with parent %i", entity, parent);
}
