#ifndef Components_SoundEmitter_h__
#define Components_SoundEmitter_h__

#include <string>

#include "Component.h"

namespace Components
{

struct SoundEmitter : Component
{
	std::string SoundFile;
	float Volume;
	float MaxRange;
};

}
#endif // !Components_SoundEmitter_h__