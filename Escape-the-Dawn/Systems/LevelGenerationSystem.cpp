#include "LevelGenerationSystem.h"


void Systems::LevelGenerationSystem::SpawnObstacle()
{
	std::shared_ptr<Components::Transform> transform;
	std::shared_ptr<Components::Bounds> bounds;
	std::shared_ptr<Components::Collision> collision;
	std::shared_ptr<Components::Model> model;

	EntityID ent;
	ent = m_World->CreateEntity();
	m_World->SetProperty(ent, "Name", std::string("Obstacle"));
	
	transform = m_World->AddComponent<Components::Transform>(ent, "Transform");
	transform->Position = glm::vec3(0,0,0); // fix position
	
	bounds = m_World->AddComponent<Components::Bounds>(ent, "Bounds");
	bounds->VolumeVector = glm::vec3(4, 4, 4);

	collision = m_World->AddComponent<Components::Collision>(ent, "Collision");

	model = m_World->AddComponent<Components::Model>(ent, "Model");
	

}
