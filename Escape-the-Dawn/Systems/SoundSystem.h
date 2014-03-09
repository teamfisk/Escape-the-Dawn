#ifndef SoundEmitter_h__
#define SoundEmitter_h__

#include "AL/al.h"
#include "AL/alc.h"

#include "System.h"
#include "Components/SoundEmitter.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <windows.h>
#include <vector>

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
	void CreateSource(int ID, float pos[3], ALboolean looping);
private:
	ALCcontext* context;
	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;

	unsigned char* buf;

	std::vector<ALuint> source;

};

}
#endif // !SoundEmitter_h__

