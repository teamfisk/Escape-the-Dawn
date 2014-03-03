#ifndef System_h__
#define System_h__

#include "Entity.h"

class World;

class System
{
public:
	System(World* world) : m_World(world) { }
	virtual ~System() { }

	virtual void Update(double dt, EntityID entity, EntityID parent) = 0;

protected:
	World* m_World;
};

#endif // System_h__