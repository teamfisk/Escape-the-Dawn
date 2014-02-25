#include "Component.h"

namespace Components
{

REGISTER_COMPONENT("Transform", Transform);
struct Transform : Component
{
	float Position[3];
};

}

