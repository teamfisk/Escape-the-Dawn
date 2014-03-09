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
	//alSourcePlay(source);
}

void Systems::SoundSystem::LoadFile(const char* fileName)
{
	FILE *fp = NULL;
	fp = fopen(strcat("Sounds/", fileName), "rb");

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

	buf = new unsigned char[dataSize];
	fread(buf, sizeof(BYTE), dataSize, fp);

	fclose(fp);
}

void Systems::SoundSystem::CreateSource(int ID, float pos[3], ALboolean looping)
{
	ALuint source;
	ALuint buffer;
	ALuint frequency = sampleRate;
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

	alBufferData(buffer, format, buf, dataSize, frequency);
	
	ALfloat SourcePos[] = { pos[0], pos[1], pos[2] };
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 }; // Playerpos? Camerapos?
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0 , 0.0, 1.0, 0.0 }; //two vectors, one defining where the listener points, and one "up" vector
	
	//Listener
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);

	//Source
	alSourcei(source, AL_BUFFER, buffer);
	alSourcef(source, AL_PITCH, 1.0f);
	alSourcef(source, AL_GAIN, 1.0f); //Volume
	alSourcefv(source, AL_POSITION, SourcePos);
	alSourcefv(source, AL_VELOCITY, SourceVel);
	alSourcei(source, AL_LOOPING, looping);
}