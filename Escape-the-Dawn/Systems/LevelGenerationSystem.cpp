#include "LevelGenerationSystem.h"

Systems::LevelGenerationSystem::LevelGenerationSystem( World* world )
	: System(world)
{
	elapsedtime = 0;
	startyz = glm::vec2(0, -200);
}

void Systems::LevelGenerationSystem::SpawnObstacle()
{
	
	
	
	typeRandom = 0 + (rand() % 5);
	

	EntityID ent;

	ent = m_World->CreateEntity();
	obstacles.push_back(ent);
	m_World->SetProperty(ent, "Name", std::string("Obstacle"));
	transform = m_World->AddComponent<Components::Transform>(ent, "Transform");
	bounds = m_World->AddComponent<Components::Bounds>(ent, "Bounds");
	collision = m_World->AddComponent<Components::Collision>(ent, "Collision");
	model = m_World->AddComponent<Components::Model>(ent, "Model");

	switch (typeRandom)
	{
	case 0:
		
		positionRandom = -500 + (rand() % 1000);
		transform->Position = glm::vec3( positionRandom, startyz); // fix position
		bounds->VolumeVector = glm::vec3(4, 4, 4);
		model->ModelFile = "Models/obstacle_mountain_1.obj";

		break;
	case 1:

		positionRandom = -100 + (rand() % 200);
		transform->Position = glm::vec3( positionRandom, startyz); // fix position
		bounds->VolumeVector = glm::vec3(4, 4, 4);
		model->ModelFile = "Models/obstacle_mountain_2.obj";

		break;
	case 2:

		positionRandom = -100 + (rand() % 200);
		transform->Position = glm::vec3( positionRandom, startyz); // fix position
		bounds->VolumeVector = glm::vec3(4, 4, 4);
		model->ModelFile = "Models/obstacle_mountain_3.obj";

		break;
	case 3:

		positionRandom = -100 + (rand() % 200);
		transform->Position = glm::vec3( positionRandom, startyz); // fix position
		bounds->VolumeVector = glm::vec3(4, 4, 4);
		model->ModelFile = "Models/obstacle_mountain_4.obj";

		break;
	case 4:

		positionRandom = -100 + (rand() % 200);
		transform->Position = glm::vec3( positionRandom, startyz); // fix position
		bounds->VolumeVector = glm::vec3(4, 4, 4);
		model->ModelFile = "Models/obstacle_cube_1.obj";

		break;
	default:
		break;
	}
	
}

void Systems::LevelGenerationSystem::Update( double dt )
{
	
	elapsedtime += dt;

	if(elapsedtime > 1.0){
		SpawnObstacle();
		elapsedtime = 0;
	}

	for(auto ent : obstacles)
	{
		auto transformComponent = m_World->GetComponent<Components::Transform>(ent, "Transform");
		transformComponent->Position.z += 15.f * dt;
	}
}


