#include "SoundSystem.h"
#include "World.h"
#include <AL/al.h>
#include <AL/alc.h>

System::SoundSystem::SoundSystem(World* world)
{
	ALCdevice* Device = alcOpenDevice(nullptr);

	if(Device)
	{
		context = alcCreateContext(Device, nullptr);
		alcMakeContextCurrent(context);
	}


}

void System::SoundSystem::Update(double dt)
{

}

void System::SoundSystem::Update(double dt, EntityID entity, EntityID parent)
{
	auto soundEmitter = m_World->GetComponent<Components::SoundEmitter>(entity, "SoundEmitter");
	if(soundEmitter == nullptr)
		return;

	
}

void System::SoundSystem::PlaySound(std::shared_ptr<Components::SoundEmitter> emitter, std::string fileName)
{
	LoadFile(fileName);
}

void System::SoundSystem::LoadFile(std::string fileName)
{
	loadWavFile()
}