#ifndef LevelGenerationSystem_h__
#define LevelGenerationSystem_h__

#include "System.h"

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