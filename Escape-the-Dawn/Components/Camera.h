#ifndef Components_Camera_h__
#define Components_Camera_h__

#include "Component.h"

namespace Components
{

struct Camera : Component
{
	float FOV;
	float NearClip;
	float FarClip;
};

}
#endif // !Components_Camera_h__