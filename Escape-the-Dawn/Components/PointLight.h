#ifndef PointLight_h__
#define PointLight_h__

#include "Component.h"
#include "Color.h"

namespace Components
{

	struct PointLight : Component
	{
		float Intensity;
		float MaxRange;
		float SpecularIntensity;
		Color color;
	};
	REGISTER_COMPONENT("PointLight", PointLight);

}
#endif // !PointLight_h__