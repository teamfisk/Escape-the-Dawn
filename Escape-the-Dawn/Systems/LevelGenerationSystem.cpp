#include "LevelGenerationSystem.h"

Systems::LevelGenerationSystem::LevelGenerationSystem( World* world )
	: System(world)
{
	elapsedtime = 0;

	
	startx = 0;
	startyz = glm::vec2(0, -1000);
}

void Systems::LevelGenerationSystem::SpawnObstacle()
{
	typeRandom = 0 + (rand() % 3);

	EntityID ent;

	ent = m_World->CreateEntity();
	obstacles.push_back(ent);
	m_World->SetProperty(ent, "Name", std::string("Obstacle"));
	transform = m_World->AddComponent<Components::Transform>(ent, "Transform");
	bounds = m_World->AddComponent<Components::Bounds>(ent, "Bounds");
	collision = m_World->AddComponent<Components::Collision>(ent, "Collision");
	model = m_World->AddComponent<Components::Model>(ent, "Model");

	positionRandom = -500 + startx + (rand() % 1000);

	switch (typeRandom)
	{
	case 0: // Mountain stuff :D
		{
		transform->Position = glm::vec3( positionRandom, startyz); // fix position
		float scale = (float)(rand() % 1000) / 250;
		transform->Scale = glm::vec3(scale);
		bounds->VolumeVector = glm::vec3(9, 12, 7);
		bounds->Origin = glm::vec3(1,11,-1);
		model->ModelFile = "Models/obstacle_mountain_1.obj";
		}
		break;
	case 1: // Single Mountain :D
		{
		transform->Position = glm::vec3( positionRandom, startyz); // fix position
		float scale = (float)(rand() % 1000) / 200;
		transform->Scale = glm::vec3(scale);
		bounds->VolumeVector = glm::vec3(3.5f, 7.5f, 3.5f);
		bounds->Origin = glm::vec3(0,7.5f,0);
		model->ModelFile = "Models/obstacle_mountain_2.obj";
		}
		break;
	case 2:
		{
		transform->Position = glm::vec3( positionRandom, startyz); // fix position
		float scale = (float)(rand() % 1000) / 100;
		transform->Scale = glm::vec3(scale);
		bounds->VolumeVector = glm::vec3(1, 1, 1);
		bounds->Origin = glm::vec3(0,1,0);
		model->ModelFile = "Models/obstacle_cube_1.obj";
		}
		break;
	default:

		break;
	}
	
}

void Systems::LevelGenerationSystem::Update( double dt )
{
	
	elapsedtime += dt;

	if(elapsedtime > 0.1){
		SpawnObstacle();
		elapsedtime = 0;
	}

	std::vector<EntityID> removethis;

	for(auto ent : obstacles)
	{
		auto transformComponent = m_World->GetComponent<Components::Transform>(ent, "Transform");
		transformComponent->Position.z += 100.f * dt;

		if(transformComponent->Position.z > 100)
		{
			removethis.push_back(ent);	
		}
	}

	for(auto ent : removethis)
	{
		m_World->RemoveEntity(ent);
		obstacles.remove(ent);
	}
	removethis.clear();
	
}

void Systems::LevelGenerationSystem::UpdateEntity( double dt, EntityID entity, EntityID parent )
{
	if( m_World->GetProperty<std::string>(entity, "Name") == "PlayerShip")
	{
		auto transformComponent = m_World->GetComponent<Components::Transform>(entity, "Transform");
		startyz = glm::vec2(0, transformComponent->Position.z - 1000);
		startx = transformComponent->Position.x;
	}
}


