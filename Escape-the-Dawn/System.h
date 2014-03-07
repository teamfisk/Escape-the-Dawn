#ifndef System_h__
#define System_h__

#include "Entity.h"

class World;

class System
{
public:
	System(World* world) : m_World(world) { }
	virtual ~System() { }

	// Called once per system every tick
	virtual void Update(double dt) { }
	// Called once for every entity in the world every tick
	virtual void Update(double dt, EntityID entity, EntityID parent) { }

protected:
	World* m_World;
};

#endif // System_h__