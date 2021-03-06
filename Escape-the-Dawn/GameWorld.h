#ifndef GameWorld_h__
#define GameWorld_h__

#include "World.h"
#include "Renderer.h"

#include "Systems/TransformSystem.h"
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
	GameWorld(std::shared_ptr<Renderer> renderer) 
		: m_Renderer(renderer), World() { }

	void Initialize();

	void RegisterSystems() override;
	void AddSystems() override;
	void RegisterComponents() override;

	void Update(double dt);

private:
	std::shared_ptr<Renderer> m_Renderer;
	EntityID entcamera, player2;
	EntityID m_Player;
};

#endif // GameWorld_h__
