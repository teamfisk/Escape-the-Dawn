#include "PlayerSystem.h"
#include "World.h"

Systems::PlayerSystem::PlayerSystem( World* world ) : System(world)
{
	m_PlayerSpeed = 35;
	m_PlayerOriginalBounds = glm::vec3(0);

	m_CameraOffset = glm::vec3(0.f, 5.f, 14.f);
	m_CameraOrientation = glm::angleAxis<float>(glm::radians(15.0f),glm::vec3(1,0,0));

	freecamEnabled = false;
	m_poweruptimeleft = 0;
	m_basespeed = 125.f;
	m_maxspeed = 125.f;

}

void Systems::PlayerSystem::Update(double dt)
{
	m_poweruptimeleft -= (float)dt;
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

	if (name == "Sun") {
		auto light = m_World->GetComponent<Components::PointLight>(entity, "PointLight");

		if (input->KeyState[GLFW_KEY_KP_ADD])
		{
			if (input->KeyState[GLFW_KEY_1]) {
				light->constantAttenuation += 0.001;
			}
			if (input->KeyState[GLFW_KEY_2]) {
				light->linearAttenuation += 0.001;
			}
			if (input->KeyState[GLFW_KEY_3]) {
				light->quadraticAttenuation += 0.00001;
			}
		}
		if (input->KeyState[GLFW_KEY_KP_SUBTRACT])
		{
			if (input->KeyState[GLFW_KEY_1]) {
				light->constantAttenuation -= 0.001;

			}
			if (input->KeyState[GLFW_KEY_2]) {
				light->linearAttenuation -= 0.001;

			}
			if (input->KeyState[GLFW_KEY_3]) {
				light->quadraticAttenuation -= 0.00001;

			}
		}

		//LOG_DEBUG("Constant: %f\nLinear: %f\nQuadratic: %f", light->constantAttenuation, light->linearAttenuation, light->quadraticAttenuation);
	}

	if (name == "Camera") {

		if(input->KeyState[GLFW_KEY_F4] && !input->LastKeyState[GLFW_KEY_F4]) {
			if(freecamEnabled)
				freecamEnabled = false;
			else
				freecamEnabled = true;
		}

		if(freecamEnabled)
		{
			glm::vec3 Camera_Right = glm::vec3(glm::vec4(1, 0, 0, 0) * transform->Orientation);
			glm::vec3 Camera_Forward = glm::vec3(glm::vec4(0, 0, 1, 0) * transform->Orientation);

 			float speed = m_PlayerSpeed;
 			if(input->KeyState[GLFW_KEY_LEFT_SHIFT]) {
 				speed *= 4.0f;
 			}
 			if(input->KeyState[GLFW_KEY_LEFT_ALT]) {
 				speed /= 4.0f;
 			}
 			if(input->KeyState[GLFW_KEY_A]) {
 				transform->Position -= Camera_Right * (float)dt * speed;
 			}
 			else if(input->KeyState[GLFW_KEY_D]) {
 				transform->Position += Camera_Right * (float)dt * speed;
 			}
 			if(input->KeyState[GLFW_KEY_W]) {
 				transform->Position -= Camera_Forward * (float)dt * speed;
 			}
 			if(input->KeyState[GLFW_KEY_S]) {
 				transform->Position += Camera_Forward * (float)dt * speed;
 			}
 			if(input->KeyState[GLFW_KEY_SPACE]) {
 				transform->Position += glm::vec3(0, 1, 0) * (float)dt * speed;
 			}
 			if(input->KeyState[GLFW_KEY_LEFT_CONTROL]) {
 				transform->Position -= glm::vec3(0, 1, 0) * (float)dt * speed;
 			}

			if (input->MouseState[GLFW_MOUSE_BUTTON_LEFT]) {
				// TOUCHING THIS CODE MIGHT COUSE THE UNIVERSE TO IMPLODE, ALSO DRAGONS
				//---------------------------------------------------------------------
				transform->Orientation = glm::angleAxis<float>(input->dY/300.f,glm::vec3(1,0,0)) * transform->Orientation;

				transform->Orientation = transform->Orientation * glm::angleAxis<float>(input->dX/300.f,glm::vec3(0,1,0));
				//---------------------------------------------------------------------
				// TOUCHING THIS CODE MIGHT COUSE THE UNIVERSE TO IMPLODE, ALSO DRAGONS
			}
		}
		
	}


	if (name == "Player") 
	{
		auto bounds = m_World->GetComponent<Components::Bounds>(entity, "Bounds");
		if (bounds && m_PlayerOriginalBounds == glm::vec3(0)) {
			m_PlayerOriginalBounds = bounds->VolumeVector;
		}

		auto soundEmitter = m_World->GetComponent<Components::SoundEmitter>(entity, "SoundEmitter");

		glm::vec3 Ship_Right = glm::vec3(glm::vec4(1, 0, 0, 0));
		glm::vec3 Ship_Forward = glm::vec3(glm::vec4(0, 0, 1, 0));

		float TurnSpeed = 1.0f;
		glm::vec3 Euler = glm::degrees(glm::eulerAngles(transform->Orientation));

		// Controls
		if(input->KeyState[GLFW_KEY_LEFT]) {
			transform->Position -= Ship_Right * (float)dt * (m_PlayerSpeed + Euler.z);
			
			if(Euler.z < 10.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed,glm::vec3(0,0,1));
			}
			else if(Euler.z < 20.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed/2,glm::vec3(0,0,1));
			}
			else if (Euler.z < 25.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed/4,glm::vec3(0,0,1));
			}
		}
		else if(input->KeyState[GLFW_KEY_RIGHT]) {
			transform->Position += Ship_Right * (float)dt * (m_PlayerSpeed - Euler.z);

			if(Euler.z > -10.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed,glm::vec3(0,0,-1));
			}
			else if(Euler.z > -20.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed/2,glm::vec3(0,0,-1));
			}
			else if (Euler.z > -25.f)
			{
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt * TurnSpeed/4,glm::vec3(0,0,-1));
			}
		}
		else
		{
			transform->Position -= Ship_Right * (float)dt *  Euler.z;
			if(Euler.z < 1.5f && Euler.z > -1.5f)
				transform->Orientation = glm::angleAxis<float>(0,glm::vec3(0,0,1));
			else if(Euler.z < 0.f)
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt,glm::vec3(0,0,1));
			else if(Euler.z > 0.f)
				transform->Orientation = transform->Orientation * glm::angleAxis<float>((float)dt,glm::vec3(0,0,-1));
		}

		// Update player bounds based on rotation
		if (bounds) {
			Euler = glm::eulerAngles(transform->Orientation);
			bounds->VolumeVector.x = m_PlayerOriginalBounds.x * glm::cos(glm::radians(Euler.z));
		}
		
		auto cameraEntity = m_World->GetProperty<EntityID>(entity, "Camera");
		auto cameracamera = m_World->GetComponent<Components::Camera>(cameraEntity, "Camera");
		cameracamera->FOV = glm::radians(45.f + transform->Velocity.z/3.f );

		auto collision = m_World->GetComponent<Components::Collision>(entity, "Collision");
		if(collision != nullptr)
		{
			// Obstacle collision
			for(auto ent : collision->CollidingEntities)
			{
				if(m_World->GetProperty<std::string>(ent, "Name") == "Obstacle")
				{
					
					auto deathSoundEntity = m_World->CreateEntity(ent);

					auto deathTransform = m_World->AddComponent<Components::Transform>(deathSoundEntity, "Transform");
					auto deathSoundEmitter = m_World->AddComponent<Components::SoundEmitter>(deathSoundEntity, "SoundEmitter");
					deathSoundEmitter->Gain = 5.f;
					deathSoundEmitter->ReferenceDistance = 1.5f;

					auto deathSoundSystem = m_World->GetSystem<Systems::SoundSystem>("SoundSystem");
					deathSoundSystem->PlaySound(deathSoundEmitter.get(), "Sounds/Explosion3.wav");

					m_World->RemoveEntity(entity);

					//TODO: Ljud som kommer från crashsite
				}

				if (m_World->GetProperty<std::string>(ent, "Name") == "Obstacle_SoundTrigger")
				{
					auto parent = m_World->GetEntityParent(ent);
					auto swoosh = m_World->CreateEntity(parent);
					m_World->AddComponent<Components::Transform>(swoosh, "Transform");
					auto swooshSound = m_World->AddComponent<Components::SoundEmitter>(swoosh, "SoundEmitter");
					swooshSound->Gain = 2.f;
					swooshSound->MaxDistance = 5.f;
					swooshSound->ReferenceDistance = 1.f;
					auto soundSystem = m_World->GetSystem<Systems::SoundSystem>("SoundSystem");
					soundSystem->PlaySound(swooshSound.get(), "Sounds/swoosh.wav");
					m_World->RemoveEntity(ent);
				}
			}

			//powerup
			for(auto ent : collision->CollidingEntities)
			{
				std::string name = m_World->GetProperty<std::string>(ent, "Name");
				if(name == "PowerUp")
				{
					auto powerupComp = m_World->GetComponent<Components::PowerUp>(ent, "PowerUp");
					m_maxspeed = powerupComp->Speed;
					m_poweruptimeleft = 5.f;
					m_World->RemoveEntity(ent);
					SetPlayerLightColor(entity, glm::vec3(0.0, 1.0, 0.0));
					auto soundSystem = m_World->GetSystem<Systems::SoundSystem>("SoundSystem");
					soundSystem->PlaySound(soundEmitter, "Sounds/boom.wav");
				}
			}
			if(m_poweruptimeleft <= 0)
			{
				m_maxspeed = m_basespeed;
				SetPlayerLightColor(entity, glm::vec3(0.05f, 0.36f, 1.f));
			}
			if(transform->Velocity.z < m_maxspeed)
			{
				transform->Velocity.z += 100.f*dt;
				if(transform->Velocity.z >= m_maxspeed)
					transform->Velocity.z = m_maxspeed;
			}
			else if(transform->Velocity.z > m_maxspeed)
			{
				transform->Velocity.z -= 50.f*dt;
				if(transform->Velocity.z <= m_maxspeed)
					transform->Velocity.z = m_maxspeed;
			}
		}

		// Update camera
		if(! freecamEnabled)
		{
			auto cameraTransform = m_World->GetComponent<Components::Transform>(cameraEntity, "Transform");
			if (cameraTransform) {
				cameraTransform->Position = transform->Position + m_CameraOffset;
				cameraTransform->Orientation = m_CameraOrientation;
			}
			
			
		}

		// Update ground
		auto groundEntity = m_World->GetProperty<EntityID>(entity, "Ground");
		if (m_World->ValidEntity(groundEntity)) {
			auto groundTransform = m_World->GetComponent<Components::Transform>(groundEntity, "Transform");
			groundTransform->Position.x = transform->Position.x;
		}

		// Update Sun
		auto sunEntity = m_World->GetProperty<EntityID>(entity, "Sun");
		if (m_World->ValidEntity(sunEntity)) {
			auto sunTransform = m_World->GetComponent<Components::Transform>(sunEntity, "Transform");
			sunTransform->Position.x = transform->Position.x;
		}
	}
}

void Systems::PlayerSystem::SetPlayerLightColor(EntityID player, glm::vec3 color)
{
	auto light1 = m_World->GetProperty<EntityID>(player, "LightLeft");
	auto light2 = m_World->GetProperty<EntityID>(player, "LightRight");
	
	auto lightComponent1 = m_World->GetComponent<Components::PointLight>(light1, "PointLight");
	auto lightComponent2 = m_World->GetComponent<Components::PointLight>(light2, "PointLight");

	lightComponent1->Diffuse = color;
	lightComponent2->Diffuse = color;
}

