#ifndef Sprite_h__
#define Sprite_h__

#include "Component.h"
#include "Color.h"

namespace Components
{

	struct Sprite : Component
	{
		std::string SpriteFile;
		Color color;
	};
	REGISTER_COMPONENT("Sprite", Sprite);

}
#endif // !Sprite_h__