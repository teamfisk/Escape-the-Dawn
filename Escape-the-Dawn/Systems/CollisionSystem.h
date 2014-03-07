#ifndef CollisionSystem_h__
#define CollisionSystem_h__

#include "System.h"
#include "logging.h"

#include "Components/Transform.h"

namespace Systems
{

class Collision : public System
{
public:
	Collision(World* world) : System(world) { }

	void Update(double dt, EntityID entity, EntityID parent) override;
};

}

#endif // CollisionSystem_h__
