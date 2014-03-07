#ifndef Bounds_h__
#define Bounds_h__

#include "Component.h"
#include <glm/common.hpp>


namespace Components
{

	struct Bounds : Component
	{
		//Axis Aligned Bounding Box
		glm::vec3 origin;
		glm::vec3 volumeVector; //The vector that defines the volume of the BB, it goes from one corner to the opposite one
	};
	REGISTER_COMPONENT("Bounds", Bounds);

}
#endif // !Bounds_h__