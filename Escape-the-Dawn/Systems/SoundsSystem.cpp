#include "SoundSystem.h"
#include "World.h"
#include <AL/al.h>
#include <AL/alc.h>

Systems::SoundSystem::SoundSystem(World* world)
	 : System(world)
{
	ALCdevice* Device = alcOpenDevice(nullptr);

	if(Device)
	{
		context = alcCreateContext(Device, nullptr);
		alcMakeContextCurrent(context);
	}


}

void Systems::SoundSystem::Update(double dt)
{

}

void Systems::SoundSystem::UpdateEntity(double dt, EntityID entity, EntityID parent)
{
	auto soundEmitter = m_World->GetComponent<Components::SoundEmitter>(entity, "SoundEmitter");
	if(soundEmitter == nullptr)
		return;

	
}

void Systems::SoundSystem::PlaySound(std::shared_ptr<Components::SoundEmitter> emitter, std::string fileName)
{
	LoadFile(fileName);
}

void Systems::SoundSystem::LoadFile(std::string fileName)
{
	//loadWavFile()
}