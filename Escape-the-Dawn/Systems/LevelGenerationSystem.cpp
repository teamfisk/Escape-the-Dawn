#include "LevelGenerationSystem.h"

Systems::LevelGenerationSystem::LevelGenerationSystem( World* world )
	: System(world)
{
	elapsedtime = 0;
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
	auto sound = m_World->AddComponent<Components::SoundEmitter>(ent, "SoundEmitter");
	//pointLight = m_World->AddComponent<Components::PointLight>(ent, "PointLight");

	positionRandom = -500 + (rand() % 1000);
	transform->Position = glm::vec3(positionRandom, startyz); // fix position
	transform->Velocity = glm::vec3(0.f, 10.f, 100.f);

	sound->Loop = true;
	sound->Gain = 1.f;
	sound->ReferenceDistance = 15.f;
	m_World->GetSystem<Systems::SoundSystem>("SoundSystem")->PlaySound(sound, "Sounds/hum.wav");

	switch (typeRandom)
	{
	case 0:
		bounds->VolumeVector = glm::vec3(9, 12, 7);
		bounds->Origin = glm::vec3(1,11,-1);
		model->ModelFile = "Models/obstacle_mountain_1.obj";

		break;
	case 1:
		bounds->VolumeVector = glm::vec3(3.5f, 7.5f, 3.5f);
		bounds->Origin = glm::vec3(0,7.5f,0);
		model->ModelFile = "Models/obstacle_mountain_2.obj";

		break;
	case 2:
		bounds->VolumeVector = glm::vec3(1, 1, 1);
		bounds->Origin = glm::vec3(0,1,0);
	
 		//pointLight->Specular = glm::vec3(1.0,  1.0,  1.0);
 		//pointLight->Diffuse = glm::vec3(1.0,  1.0,  1.0);
 		//pointLight->Diffuse = glm::vec3(0.0,  3.0,  0.0);
 		//pointLight->constantAttenuation = 0.f;
 		//pointLight->linearAttenuation = 1.f;
 		//pointLight->quadraticAttenuation = 0.f;
 		//pointLight->spotExponent = 0.0f;
		model->ModelFile = "Models/obstacle_cube_1.obj";

		break;
	default:

		break;
	}

	// Put it below ground level
	transform->Position.y -= bounds->VolumeVector.y * 2.f;
	
}

void Systems::LevelGenerationSystem::Update( double dt )
{
	
	elapsedtime += dt;

	if(elapsedtime > 0.1){
		SpawnObstacle();
		elapsedtime = 0;
	}

	std::list<EntityID> removethis;

	for(auto ent : obstacles)
	{
		auto transform = m_World->GetComponent<Components::Transform>(ent, "Transform");
		transform->Position += transform->Velocity * (float)dt;

		// Stop raising obstacles when they reach ground level
		if (transform->Velocity.y > 0 && transform->Position.y >= 0) {
			transform->Position.y = 0;
			transform->Velocity.y = 0;
		}

		if(transform->Position.z > 800)
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


