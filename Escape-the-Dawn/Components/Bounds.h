#ifndef Components_Bounds_h__
#define Components_Bounds_h__

#include "Component.h"
#include "AABB.h"

namespace Components
{

struct Bounds : Component
{
	AABB BoundingBox; //Axis Aligned Bounding Box
};

}
#endif // !Components_Bounds_h__