#ifndef Components_Model_h__
#define Components_Model_h__

#include <string>

#include "Component.h"
#include "Color.h"

namespace Components
{

struct Model : Component
{
	Model() : Visible(true) { }
	std::string ModelFile;
	Color Color;
	bool Visible;
};

}
#endif // !Components_Model_h__