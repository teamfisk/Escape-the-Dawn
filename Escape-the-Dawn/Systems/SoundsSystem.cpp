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
	auto transformComponent = m_World->GetComponent<Components::Transform>(entity, "Transform");
	if (transformComponent == nullptr)
		return;

	auto entityName = m_World->GetProperty<std::string>(entity, "Name");
	if (entityName == "Player")
	{
		glm::vec3 playerPos = transformComponent->Position;
		ALfloat listenerPos[3] = { playerPos.x, playerPos.y, playerPos.z };

		glm::vec3 playerVel = transformComponent->Velocity;
		ALfloat listenerVel[3] = { playerVel.x, playerVel.y, playerVel.z };

		glm::fquat playerQuatOri = transformComponent->Orientation;
		glm::vec3 playerOriFW = glm::rotate(playerQuatOri, glm::vec3(0, 0, -1));
		glm::vec3 playerOriUP = glm::rotate(playerQuatOri, glm::vec3(0, 1, 0));
		ALfloat listenerOri[6] = { playerOriFW.x, playerOriFW.y, playerOriFW.z, playerOriUP.x, playerOriUP.y, playerOriUP.z };

		//Listener
		alListenerfv(AL_POSITION, listenerPos);
		alListenerfv(AL_VELOCITY, listenerVel);
		alListenerfv(AL_ORIENTATION, listenerOri);
	}

	auto soundEmitter = m_World->GetComponent<Components::SoundEmitter>(entity, "SoundEmitter");
	if(soundEmitter != nullptr)
	{
		alSourcef(source[soundEmitter.get()], AL_GAIN, soundEmitter->Gain); //Volume
		alSourcei(source[soundEmitter.get()], AL_MAX_DISTANCE, soundEmitter->MaxDistance);
		alSourcei(source[soundEmitter.get()], AL_REFERENCE_DISTANCE, soundEmitter->ReferenceDistance);
		alSourcef(source[soundEmitter.get()], AL_PITCH, soundEmitter->Pitch); 
		alSourcei(source[soundEmitter.get()], AL_LOOPING, soundEmitter->Loop);

		glm::vec3 emitterPos = transformComponent->Position;
		ALfloat sourcePos[3] = { emitterPos.x, emitterPos.y, emitterPos.z };

		glm::vec3 emitterVel= transformComponent->Position;
		ALfloat sourceVel[3] = { emitterVel.x, emitterVel.y, emitterVel.z };

		alSourcefv(source[soundEmitter.get()], AL_POSITION, sourcePos);
		alSourcefv(source[soundEmitter.get()], AL_VELOCITY, sourceVel);
	}
}

void Systems::SoundSystem::PlaySound(std::shared_ptr<Components::SoundEmitter> emitter, std::string fileName)
{
	alSourcePlay(source[emitter.get()]);
}

void Systems::SoundSystem::OnComponentCreated(std::string type, std::shared_ptr<Component> component)
{
	if(type == "SoundEmitter")
		source[component.get()] = CreateSource();
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

ALuint Systems::SoundSystem::CreateSource()
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

	return source;
}