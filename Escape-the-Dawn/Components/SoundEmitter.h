#ifndef SoundEmitter_h__
#define SoundEmitter_h__

#include "Component.h"

namespace Components
{

	struct SoundEmitter : Component
	{
		std::string SoundFile;
		float Volume;
		float MaxRange;
	};
	REGISTER_COMPONENT("SoundEmitter", SoundEmitter);

}
#endif // !SoundEmitter_h__