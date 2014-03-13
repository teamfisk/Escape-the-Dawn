#include "LevelGenerationSystem.h"

Systems::LevelGenerationSystem::LevelGenerationSystem( World* world )
	: System(world)
{
	elapsedtime = 0;

	velocity = 0;
	startx = 0;
	startyz = glm::vec2(0, -1000);
}

void Systems::LevelGenerationSystem::SpawnObstacle()
{
	typeRandom = 0 + (rand() % 10);

	EntityID ent;

	ent = m_World->CreateEntity();
	obstacles.push_back(ent);
	m_World->SetProperty(ent, "Name", std::string("Obstacle"));
	transform = m_World->AddComponent<Components::Transform>(ent, "Transform");
	bounds = m_World->AddComponent<Components::Bounds>(ent, "Bounds");
	collision = m_World->AddComponent<Components::Collision>(ent, "Collision");
	model = m_World->AddComponent<Components::Model>(ent, "Model");
	auto sound = m_World->AddComponent<Components::SoundEmitter>(ent, "SoundEmitter");
	

	positionRandom = -500 + startx + (rand() % 1000);
	transform->Position = glm::vec3(positionRandom, startyz);
	//transform->Velocity = glm::vec3(0.f, 10.f, 100.f);

	sound->Loop = true;
	sound->Gain = 1.f;
	sound->ReferenceDistance = 15.f;
	m_World->GetSystem<Systems::SoundSystem>("SoundSystem")->PlaySound(sound, "Sounds/hum.wav");

	if(typeRandom >= 0 && typeRandom < 2) // Mountain stuff :D
		{
		float scale = (float)(rand() % 1000) / 250;
		transform->Scale = glm::vec3(scale);
		bounds->VolumeVector = glm::vec3(9, 12, 7);
		bounds->Origin = glm::vec3(1,11,-1);
		model->ModelFile = "Models/obstacle_mountain_1.obj";
		}
	else if(typeRandom >= 2 && typeRandom < 5) // Single Mountain :D
		{
		float scale = (float)(rand() % 1000) / 200;
		transform->Scale = glm::vec3(scale);
		bounds->VolumeVector = glm::vec3(3.5f, 7.5f, 3.5f);
		bounds->Origin = glm::vec3(0,7.5f,0);
		model->ModelFile = "Models/obstacle_mountain_2.obj";
		}
	else if(typeRandom >= 5 && typeRandom < 8)
		{
		float scale = (float)(rand() % 1000) / 100;
		transform->Scale = glm::vec3(scale);
		bounds->VolumeVector = glm::vec3(1, 1, 1);
		bounds->Origin = glm::vec3(0,1,0);
		model->ModelFile = "Models/obstacle_cube_1.obj";
		}
	if(typeRandom >= 8 && typeRandom < 10)
		{
			float scale = (float)(rand() % 1000) / 100;
			bounds->VolumeVector = glm::vec3(4, 4, 4);
			bounds->Origin = glm::vec3(0,4,0);
			

			powerUp = m_World->AddComponent<Components::PowerUp>(ent, "PowerUp");
			powerUp->Speed = 10.f;

			model->ModelFile = "Models/powerup.obj";
		}
	

	// Put it below ground level
	//transform->Position.y -= bounds->VolumeVector.y * 2.f;
	
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
		auto model = m_World->GetComponent<Components::Model>(ent, "Model");

		transform->Velocity.z = velocity;
		transform->Position += transform->Velocity * (float)dt;

		// Stop raising obstacles when they reach ground level
		if (transform->Velocity.y > 0 && transform->Position.y >= 0) {
			transform->Position.y = 0;
			transform->Velocity.y = 0;
		}

		if (transform->Position.z > 10 && model->Visible)
		{
			model->Visible = false;
		}

		if(transform->Position.z > 2000)
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
	if( m_World->GetProperty<std::string>(entity, "Name") == "Player")
	{
		auto transformComponent = m_World->GetComponent<Components::Transform>(entity, "Transform");
		startyz = glm::vec2(0, transformComponent->Position.z - 1000);
		startx = transformComponent->Position.x;
		velocity = transformComponent->Velocity.z;
	}
}


