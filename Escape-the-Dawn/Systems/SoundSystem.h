#ifndef SoundEmitter_h__
#define SoundEmitter_h__

#include "AL/al.h"
#include "AL/alc.h"

#include "System.h"
#include "Components/SoundEmitter.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <windows.h>

namespace Systems
{

class SoundSystem : public System
{
public:
	SoundSystem(World* world);

	void Update(double dt) override;
	void UpdateEntity(double dt, EntityID entity, EntityID parent) override;
	void OnComponentCreated(std::string type, std::shared_ptr<Component> component) override;
	void PlaySound(std::shared_ptr<Components::SoundEmitter> emitter, std::string fileName);
	void LoadFile(const char* fileName);
	void CreateListener(int ID);
	void CreateSource(int ID);
private:
	ALCcontext* context;
	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;

};

}
#endif // !SoundEmitter_h__

