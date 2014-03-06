#ifndef Transform_h__
#define Transform_h__

#include "Component.h"
#include <glm/gtc/quaternion.hpp>

namespace Components
{

	struct Transform : Component
	{
		float Position[3];
		glm::fquat qtrn; //Quaternion with floats
		float Velocity[3];
	};
	REGISTER_COMPONENT("Transform", Transform);

}
#endif // Transform_h__
