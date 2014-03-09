#ifndef SoundEmitter_h__
#define SoundEmitter_h__

#include "System.h"
#include "Components/SoundEmitter.h"

namespace System
{

class SoundSystem : public System
{
public:
	SoundSystem(World* world) : System(world)
	{

	}
	void Update(double dt) override;
	void Update(double dt, EntityID entity, EntityID parent) override;
	void OnComponentCreated(std::string type, std::shared_ptr<Component> component) override;
	void PlaySound(std::shared_ptr<Components::SoundEmitter> emitter, std::string fileName);
	void LoadFile(std::string fileName);
private:
	ALCcontext* context;

};

}
#endif // !SoundEmitter_h__

