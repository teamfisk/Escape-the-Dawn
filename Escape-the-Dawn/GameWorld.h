#ifndef GameWorld_h__
#define GameWorld_h__

#include "World.h"
#include "Renderer.h"

#include "Systems/CollisionSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/LevelGenerationSystem.h"
#include "Systems/ParticleSystem.h"
#include "Systems/PlayerSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/SoundSystem.h"

#include "Components/Bounds.h"
#include "Components/Camera.h" 
#include "Components/Collision.h" 
#include "Components/DirectionalLight.h" 
#include "Components/Input.h" 
#include "Components/Model.h" 
#include "Components/ParticleEmitter.h" 
#include "Components/PointLight.h" 
#include "Components/PowerUp.h" 
#include "Components/SoundEmitter.h" 
#include "Components/Sprite.h" 
#include "Components/Stat.h" 
#include "Components/Template.h" 
#include "Components/Transform.h" 

class GameWorld : public World
{
public:
	GameWorld(std::shared_ptr<Renderer> renderer);
	void Initialize() override;

	void RegisterSystems() override;
	void RegisterComponents() override;

	void Update(double dt) override;

private:
	std::shared_ptr<Renderer> m_Renderer;
};

GameWorld::GameWorld(std::shared_ptr<Renderer> renderer)
	: m_Renderer(renderer), World()
{

}

void GameWorld::Initialize()
{
	World::Initialize();

	//AddSystem("LevelGenerationSystem");
	AddSystem("InputSystem");
	//AddSystem("CollisionSystem");
	//AddSystem("ParticleSystem");
	AddSystem("PlayerSystem");
	AddSystem("SoundSystem");
	AddSystem("RenderSystem");

	std::shared_ptr<Components::Transform> transform;
	std::shared_ptr<Components::Model> model;
	std::shared_ptr<Components::Camera> camera;
	EntityID ent;

	ent = CreateEntity();
	transform = AddComponent<Components::Transform>(ent, "Transform");
	transform->Position = glm::vec3(0.f, 0.f, 0.f);
	model = AddComponent<Components::Model>(ent, "Model");
	model->ModelFile = "ship.obj";
	auto soundEmitter = AddComponent<Components::SoundEmitter>(ent, "SoundEmitter");
	soundEmitter->Gain = 1;
	soundEmitter->MaxDistance = FLT_MAX;
	soundEmitter->ReferenceDistance = 10;
	soundEmitter->Loop = true;
	
	soundEmitter->Pitch = 1;
	GetSystem<Systems::SoundSystem>("SoundSystem")->PlaySound(soundEmitter, "Sounds/hallelujah.wav");
	

	ent = CreateEntity();
	SetProperty(ent, "Name", std::string("Camera"));
	transform = AddComponent<Components::Transform>(ent, "Transform");
	AddComponent<Components::Input>(ent, "Input");
	transform->Position = glm::vec3(0.f, 2.f, 10.f);
	camera = AddComponent<Components::Camera>(ent, "Camera");
	camera->FOV		= 45.f;
	camera->FarClip	= 1000.f;
	camera->NearClip	= 0.01f;
	transform->Orientation = glm::angleAxis<float>(glm::radians(25.0f),glm::vec3(1,0,0));
}

void GameWorld::RegisterSystems()
{
	//m_SystemFactory.Register("LevelGenerationSystem", [this]() { return new Systems::LevelGenerationSystem(this); });
	m_SystemFactory.Register("InputSystem", [this]() { return new Systems::InputSystem(this, m_Renderer); });
	//m_SystemFactory.Register("CollisionSystem", [this]() { return new Systems::CollisionSystem(this); });
	//m_SystemFactory.Register("ParticleSystem", [this]() { return new Systems::ParticleSystem(this); });
	m_SystemFactory.Register("PlayerSystem", [this]() { return new Systems::PlayerSystem(this); });
	m_SystemFactory.Register("SoundSystem", [this]() { return new Systems::SoundSystem(this); });
	m_SystemFactory.Register("RenderSystem", [this]() { return new Systems::RenderSystem(this, m_Renderer); });
}

void GameWorld::RegisterComponents()
{
	m_ComponentFactory.Register("Bounds", []() { return new Components::Bounds(); });
	m_ComponentFactory.Register("Camera", []() { return new Components::Camera(); });
	m_ComponentFactory.Register("Collision", []() { return new Components::Collision(); });
	m_ComponentFactory.Register("DirectionalLight", []() { return new Components::DirectionalLight(); });
	m_ComponentFactory.Register("Input", []() { return new Components::Input(); });
	m_ComponentFactory.Register("Model", []() { return new Components::Model(); });
	m_ComponentFactory.Register("ParticleEmitter", []() { return new Components::ParticleEmitter(); });
	m_ComponentFactory.Register("PointLight", []() { return new Components::PointLight(); });
	m_ComponentFactory.Register("PowerUp", []() { return new Components::PowerUp(); });
	m_ComponentFactory.Register("SoundEmitter", []() { return new Components::SoundEmitter(); });
	m_ComponentFactory.Register("Sprite", []() { return new Components::Sprite(); });
	m_ComponentFactory.Register("Stat", []() { return new Components::Stat(); });
	m_ComponentFactory.Register("Template", []() { return new Components::Template(); });
	m_ComponentFactory.Register("Transform", []() { return new Components::Transform(); });
}

void GameWorld::Update(double dt)
{
	World::Update(dt);
}

#endif // GameWorld_h__
