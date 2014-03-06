#ifndef Template_h__
#define Template_h__

#include "Component.h"

namespace Components
{

	struct Template : Component { };
	REGISTER_COMPONENT("Template", Template);

}
#endif // !Template_h__