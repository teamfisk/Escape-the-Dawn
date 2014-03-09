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

	AddSystem("InputSystem");
}

void GameWorld::RegisterSystems()
{
	//m_SystemFactory.Register("LevelGenerationSystem", [this]() { return new Systems::LevelGenerationSystem(this); });
	m_SystemFactory.Register("InputSystem", [this]() { return new Systems::InputSystem(this, m_Renderer); });
	//m_SystemFactory.Register("CollisionSystem", [this]() { return new Systems::CollisionSystem(this); });
	//m_SystemFactory.Register("ParticleSystem", [this]() { return new Systems::ParticleSystem(this); });
	//m_SystemFactory.Register("PlayerSystem", [this]() { return new Systems::PlayerSystem(this); });
	//m_SystemFactory.Register("SoundSystem", [this]() { return new Systems::SoundSystem(this); });
	//m_SystemFactory.Register("RenderSystem", [this]() { return new Systems::RenderSystem(this, m_Renderer); });
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
