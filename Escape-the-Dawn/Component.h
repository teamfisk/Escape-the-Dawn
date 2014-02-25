#ifndef Component_h__
#define Component_h__

#include <memory>

#include "Entity.h"
#include "ComponentFactory.h"

struct Component
{
	EntityID Entity;
};

#endif // Component_h__