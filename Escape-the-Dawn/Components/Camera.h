#ifndef Components_Camera_h__
#define Components_Camera_h__

#include "Component.h"

namespace Components
{

struct Camera : Component
{
	int FOV;
	int NearClip;
	int FarClip;
};

}
#endif // !Components_Camera_h__