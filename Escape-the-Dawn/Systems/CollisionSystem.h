#ifndef CollisionSystem_h__
#define CollisionSystem_h__

#include "System.h"
#include "logging.h"

#include "Components/Transform.h"

namespace Systems
{

class CollisionSystem : public System
{
public:
	CollisionSystem(World* world) 
		: System(world) { }

	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;
};

}

#endif // CollisionSystem_h__
