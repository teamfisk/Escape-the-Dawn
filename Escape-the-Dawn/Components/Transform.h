#ifndef Transform_h__
#define Transform_h__

#include "Component.h"

namespace Components
{

struct Transform : Component
{
	float Position[3];
};
REGISTER_COMPONENT("Transform", Transform);

}

#endif // Transform_h__
