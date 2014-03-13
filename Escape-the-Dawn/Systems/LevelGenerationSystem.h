#ifndef LevelGenerationSystem_h__
#define LevelGenerationSystem_h__

#include "System.h"
#include "World.h"
#include "Components/Transform.h"
#include "Components/Bounds.h"
#include "Components/Collision.h"
#include "Components/Model.h"
#include "Components/PointLight.h"


namespace Systems
{
	class  LevelGenerationSystem : public System
	{
	public:
		LevelGenerationSystem(World* world);
			

		void SpawnObstacle();

		void Update(double dt) override;
		
	private:
		int typeRandom;
		int positionRandom;
		glm::vec2 startyz;
		double elapsedtime;

		std::list<EntityID> obstacles;
		

		std::shared_ptr<Components::Transform> transform;
		std::shared_ptr<Components::Bounds> bounds;
		std::shared_ptr<Components::Collision> collision;
		std::shared_ptr<Components::Model> model;
		std::shared_ptr<Components::PointLight> pointLight;
	};
}


#endif // LevelGenerationSystem_h__