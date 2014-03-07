#ifndef Components_PointLight_h__
#define Components_PointLight_h__

#include "Component.h"
#include "Color.h"

namespace Components
{

struct PointLight : Component
{
	float Intensity;
	float MaxRange;
	float SpecularIntensity;
	Color Color;
};

}
#endif // !Components_PointLight_h__