#ifndef Components_Collision_h__
#define Components_Collision_h__

#include "Entity.h"
#include "Component.h"
#include <vector>

namespace Components
{

struct Collision : Component
{
	bool Phantom;
	std::vector<EntityID> CollidingEntities;
};

}
#endif // !Components_Collision_h__