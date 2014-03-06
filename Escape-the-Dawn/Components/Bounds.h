#ifndef Bounds_h__
#define Bounds_h__

#include "Component.h"
#include "AABB.h"

namespace Components
{

	struct Bounds : Component
	{
		AABB BB; //Axis Aligned Bounding Box
	};
	REGISTER_COMPONENT("Bounds", Bounds);

}
#endif // !Bounds_h__