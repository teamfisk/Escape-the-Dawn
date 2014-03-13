#ifndef LevelGenerationSystem_h__
#define LevelGenerationSystem_h__

#include "System.h"
#include "Systems/SoundSystem.h"
#include "World.h"
#include "Components/Transform.h"
#include "Components/Bounds.h"
#include "Components/Collision.h"
#include "Components/Model.h"
#include "Components/PointLight.h"
#include "Components/SoundEmitter.h"
#include "Components/PowerUp.h"


namespace Systems
{
	class  LevelGenerationSystem : public System
	{
	public:
		LevelGenerationSystem(World* world);
			

		void SpawnObstacle();

		void Update(double dt) override;
		void UpdateEntity(double dt, EntityID entity, EntityID parent) override;

	private:
		int typeRandom;
		int positionRandom;
		glm::vec2 startyz;
		float startx;
		std::list<EntityID> removethis;
		double elapsedtime;

		std::list<EntityID> obstacles;
		float velocity;
	};
}


#endif // LevelGenerationSystem_h__