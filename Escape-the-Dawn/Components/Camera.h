#ifndef Camera_h__
#define Camera_h__

#include "Component.h"

namespace Components
{

	struct Camera : Component
	{
		int FOV;
		int NearClip;
		int FarClip;
	};
	REGISTER_COMPONENT("Camera", Camera);

}
#endif // !Camera_h__