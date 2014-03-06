#ifndef Stat_h__
#define Stat_h__

#include "Component.h"

namespace Components
{

	struct Stat : Component
	{
		int Health;
		bool Destroyable;
	};
	REGISTER_COMPONENT("Stat", Stat);

}
#endif // !Stat_h__