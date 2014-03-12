#ifndef LevelGenerationSystem_h__
#define LevelGenerationSystem_h__

#include "System.h"
#include "World.h"
#include "Components/Transform.h"
#include "Components/Bounds.h"
#include "Components/Collision.h"
#include "Components/Model.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

namespace Systems
{
	class  LevelGenerationSystem : public System
	{
	public:
		LevelGenerationSystem(World* world)
			: System(world) {	}

		void SpawnObstacle();

	private:
		
	};
}


#endif // LevelGenerationSystem_h__