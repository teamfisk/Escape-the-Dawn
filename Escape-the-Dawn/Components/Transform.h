#ifndef Components_Transform_h__
#define Components_Transform_h__

#include "Component.h"
#include <glm/gtc/quaternion.hpp>

namespace Components
{

struct Transform : Component
{
	glm::vec3 Position;
	glm::quat Orientation;
	glm::vec3 Velocity;
};

}

#endif // Components_Transform_h__
