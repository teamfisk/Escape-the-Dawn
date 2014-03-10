#ifndef SoundEmitter_h__
#define SoundEmitter_h__

#include "AL/al.h"
#include "AL/alc.h"

#include "System.h"
#include "Components/Transform.h"
#include "Components/SoundEmitter.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <windows.h>
#include <vector>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

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
	ALuint CreateSource();

private:
	ALCcontext* context;

	//File-info
	char type[4];
	DWORD size, chunkSize;
	short formatType, channels;
	DWORD sampleRate, avgBytesPerSec;
	short bytesPerSample, bitsPerSample;
	DWORD dataSize;
	unsigned char* buf;

	std::map<Component*, ALuint> source; 
	std::map<std::string, ALuint> buffer; // string = fileName
};

}
#endif // !SoundEmitter_h__

