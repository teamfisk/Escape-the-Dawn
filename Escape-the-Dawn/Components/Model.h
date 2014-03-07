#ifndef Components_Model_h__
#define Components_Model_h__

#include <string>

#include "Component.h"
#include "Color.h"

namespace Components
{

struct Model : Component
{
	std::string ModelFile;
	Color Color;
};

}
#endif // !Components_Model_h__