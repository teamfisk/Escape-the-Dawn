#ifndef ParticleEmitter_h__
#define ParticleEmitter_h__

#include "Component.h"
#include "Color.h"
#include <vector>

namespace Components
{

	struct ParticleEmitter : Component
	{
		int ParticleTemplate;
		float SpawnFrequency;
		int SpawnCount;
		std::vector<Color> ColorSpectrum;
		std::vector<float> ScaleSpectrum;
		float SpreadAngle;
		float LifeTime;
		std::vector<float[3]> VelocitySpectrum;
		std::vector<float[3]> AngularVelocitySpectrum;
	};
	REGISTER_COMPONENT("ParticleEmitter", ParticleEmitter);

}
#endif // !ParticleEmitter_h__