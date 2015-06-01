#include "LevelGenerationSystem.h"

Systems::LevelGenerationSystem::LevelGenerationSystem( World* world )
	: System(world)
{
	elapsedtime = 0;

	velocity = 0;
	startx = 0;
	startyz = glm::vec2(0, -1500);
	spawnFrequency = 0.1f;
}

void Systems::LevelGenerationSystem::SpawnObstacle()
{
	typeRandom = 0 + (rand() % 10);

	auto ent = m_World->CreateEntity();
	{
		auto transform = m_World->AddComponent<Components::Transform>(ent, "Transform");
		auto bounds = m_World->AddComponent<Components::Bounds>(ent, "Bounds");
		auto collision = m_World->AddComponent<Components::Collision>(ent, "Collision");
		auto model = m_World->AddComponent<Components::Model>(ent, "Model");

		positionRandom = -500 + startx + (rand() % 1000);
		transform->Position = glm::vec3(positionRandom, startyz);
		transform->Velocity = glm::vec3(0.f, 30.f, 0);

		// Obstacle
		if (typeRandom >= 0 && typeRandom < 9)
		{
			m_World->SetProperty(ent, "Name", std::string("Obstacle"));

			if (typeRandom >= 0 && typeRandom < 1) // Mountain stuff :D
			{
				float scale = 1.0f + (float)(rand() % 1000) / 250;
				transform->Scale = glm::vec3(scale);
				bounds->VolumeVector = glm::vec3(8.5f, 12, 5);
				bounds->Origin = glm::vec3(1, 11, -1);
				model->ModelFile = "Models/obstacle_mountain_1.obj";
			} 
			else if (typeRandom >= 1 && typeRandom < 5) // Single Mountain :D
			{
				float scale = 1.0f + (float)(rand() % 1000) / 200;
				transform->Scale = glm::vec3(scale);
				bounds->VolumeVector = glm::vec3(3.5f, 7.5f, 3.5f);
				bounds->Origin = glm::vec3(0, 7.5f, 0);
				model->ModelFile = "Models/obstacle_mountain_2.obj";
			} 
			else if (typeRandom >= 5 && typeRandom < 9)
			{
				float scale = 2.f + (float)(rand() % 1000) / 100;
				transform->Scale = glm::vec3(scale);
				bounds->VolumeVector = glm::vec3(1, 1, 1);
				bounds->Origin = glm::vec3(0, 1, 0);
				model->ModelFile = "Models/obstacle_cube_1.obj";
			}

			auto soundTrigger = m_World->CreateEntity(ent);
			{
				auto obstacleTransform = m_World->GetComponent<Components::Transform>(ent, "Transform");
				auto obstacleBounds = m_World->GetComponent<Components::Bounds>(ent, "Bounds");

				m_World->SetProperty(soundTrigger, "Name", std::string("Obstacle_SoundTrigger"));
				auto transform = m_World->AddComponent<Components::Transform>(soundTrigger, "Transform");
				auto bounds = m_World->AddComponent<Components::Bounds>(soundTrigger, "Bounds");
				auto collision = m_World->AddComponent<Components::Collision>(soundTrigger, "Collision");
				bounds->VolumeVector = obstacleBounds->VolumeVector * obstacleTransform->Scale + glm::vec3(25, 0, 50);
				bounds->Origin = obstacleBounds->Origin;
			}
		}

		// PowerUp
		if (typeRandom >= 9 && typeRandom < 10)
		{
			m_World->SetProperty(ent, "Name", std::string("PowerUp"));
			bounds->VolumeVector = glm::vec3(4, 4, 4);
			bounds->Origin = glm::vec3(0, 4, 0);


			auto powerUp = m_World->AddComponent<Components::PowerUp>(ent, "PowerUp");
			powerUp->Speed = 200.f;
			powerUp->Duration = 5.f;

			model->ModelFile = "Models/powerup.obj";
		}

		// Put it below ground level
		transform->Position.y -= transform->Scale.y * bounds->VolumeVector.y * 2.f;
	}

	
	
}

void Systems::LevelGenerationSystem::Update( double dt )
{
	elapsedtime += dt;
	spawnFrequency = 10/velocity;

	if(elapsedtime > spawnFrequency){
		SpawnObstacle();
		elapsedtime = 0;
	}
}

void Systems::LevelGenerationSystem::UpdateEntity( double dt, EntityID entity, EntityID parent )
{
	if( m_World->GetProperty<std::string>(entity, "Name") == "Obstacle" || m_World->GetProperty<std::string>(entity, "Name") == "PowerUp")
	{
		auto transform = m_World->GetComponent<Components::Transform>(entity, "Transform");
		transform->Velocity.z = velocity;
		transform->Position += transform->Velocity * (float)dt;

		auto name = m_World->GetProperty<std::string>(entity, "Name");
		auto pname = m_World->GetProperty<std::string>(parent, "Name");

		// Stop raising obstacles when they reach ground level
		if (transform->Velocity.y > 0 && transform->Position.y >= 0)
		{
			transform->Position.y = 0;
			transform->Velocity.y = 0;
		}

		auto model = m_World->GetComponent<Components::Model>(entity, "Model");
		if (transform->Position.z > 10 && model->Visible)
		{
			model->Visible = false;
		}

		if(transform->Position.z > 800) {
			m_World->RemoveEntity(entity);
		}
	}

	if( m_World->GetProperty<std::string>(entity, "Name") == "Player")
	{
		auto transformComponent = m_World->GetComponent<Components::Transform>(entity, "Transform");

		startyz = glm::vec2(0, transformComponent->Position.z - 1000);
		startx = transformComponent->Position.x;
		velocity = transformComponent->Velocity.z;
	}
}


