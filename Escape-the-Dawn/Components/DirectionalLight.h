#ifndef DirectionalLight_h__
#define DirectionalLight_h__

#include "Component.h"
#include "Color.h"

namespace Components
{

	struct DirectionalLight : Component
	{
		float Intensity;
		float MaxRange;
		float SpecularIntensity;
		Color color;
	};
	REGISTER_COMPONENT("DirectionalLight", DirectionalLight);

}
#endif // !DirectionalLight_h__