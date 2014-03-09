#include "SoundSystem.h"
#include "World.h"
//#include <fstream>


Systems::SoundSystem::SoundSystem(World* world)
	 : System(world)
{

	//initialize OpenAL
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
	//LoadFile(fileName);
}

void System::SoundSystem::LoadFile(const char* fileName)
{
	FILE *fp = NULL;
	fp = fopen("Sounds/" + fileName, "rb");


	//CHECK FOR VALID WAVE-FILE
	fread(type, sizeof(char), 4, fp);
	if(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F')
		return LOG_ERROR("ERROR: No RIFF in WAVE-file");

	fread(&size, sizeof(DWORD), 1, fp);
	fread(type, sizeof(char), 4, fp);
	if(type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E')
		return LOG_ERROR("ERROR: Not WAVE-file");

	fread(type, sizeof(char), 4, fp);
	if(type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' ')
		return LOG_ERROR("ERROR: No fmt in WAVE-file");

	//READ THE DATA FROM WAVE-FILE
	fread(&chunkSize, sizeof(DWORD), 1, fp);
	fread(&formatType, sizeof(short), 1, fp);
	fread(&channels, sizeof(short), 1, fp);
	fread(&sampleRate, sizeof(DWORD), 1, fp);
	fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
	fread(&bytesPerSample, sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if(type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a')
		return LOG_ERROR("ERROR: WAVE-file Missing data");

	fread(&dataSize, sizeof(DWORD), 1, fp);

	unsigned char* buf = new unsigned char[dataSize];
	fread(buf, sizeof(BYTE), dataSize, fp);

}

void System::SoundSystem::CreateSource(int ID)
{
	ALuint source;
	ALuint buffer;
	ALuint frequnzy = sampleRate;
	ALuint format = 0;

	alGenBuffers(1, &buffer);
	alGenBuffers(1, &source);

	if(bitsPerSample == 8)
	{
		if(channels == 1)
			format = AL_FORMAT_MONO8;
		else if(channels == 2)
			format = AL_FORMAT_STEREO8;
	}

	if(bitsPerSample == 16)
	{
		if (channels == 1)
			format = AL_FORMAT_MONO16;
		else if (channels == 2)
			format = AL_FORMAT_STEREO16;
	}

}