#ifndef PowerUp_h__
#define PowerUp_h__

#include "Component.h"

namespace Components
{

	struct PowerUp : Component
	{
		int Speed;
	};
	REGISTER_COMPONENT("PowerUp", PowerUp);

}
#endif // !PowerUp_h__