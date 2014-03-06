#ifndef Model_h__
#define Model_h__

#include "Component.h"
#include "Color.h"

namespace Components
{

	struct Model : Component
	{
		std::string ModelName;
		Color color;
	};
	REGISTER_COMPONENT("Model", Model);

}
#endif // !Model_h__