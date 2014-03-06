#ifndef Collision_h__
#define Collision_h__

#include "Component.h"
#include <vector>

namespace Components
{

	struct Collision : Component
	{
		bool Phantom;
		std::vector<int> CollidingEntities;
	};
	REGISTER_COMPONENT("Collision", Collision);

}
#endif // !Collision_h__