#include "SoundSystem.h"
#include "World.h"

Systems::SoundSystem::SoundSystem(World* world)
	 : System(world)
{
	//initialize OpenAL
	ALCdevice* Device = alcOpenDevice(NULL);
	ALCcontext* context;
	if(Device)
	{
		context = alcCreateContext(Device, NULL);
		alcMakeContextCurrent(context);
	}
	else
	{
		LOG_ERROR("OMG OPEN AL FAIL");
	}

	alGetError();
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
	if (entityName == "Camera")
	{
		glm::vec3 playerPos = transformComponent->Position;
		ALfloat listenerPos[3] = { playerPos.x, playerPos.y, -playerPos.z };

		glm::vec3 playerVel = transformComponent->Velocity;
		ALfloat listenerVel[3] = { playerVel.x, playerVel.y, -playerVel.z };

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
		ALuint source = m_Source[soundEmitter];
		alSourcei(source, AL_GAIN, soundEmitter->Gain);
		alSourcei(source, AL_MAX_DISTANCE, soundEmitter->MaxDistance);
		alSourcei(source, AL_REFERENCE_DISTANCE, soundEmitter->ReferenceDistance);
		alSourcef(source, AL_PITCH, soundEmitter->Pitch); 
		alSourcei(source, AL_LOOPING, soundEmitter->Loop);

		glm::vec3 emitterPos = transformComponent->Position;
		ALfloat sourcePos[3] = { emitterPos.x, emitterPos.y, -emitterPos.z };

		glm::vec3 emitterVel= transformComponent->Velocity;
		ALfloat sourceVel[3] = { emitterVel.x, emitterVel.y, -emitterVel.z };

		alSourcefv(source, AL_POSITION, sourcePos);
		alSourcefv(source, AL_VELOCITY, sourceVel);
	}
}

void Systems::SoundSystem::PlaySound(std::shared_ptr<Components::SoundEmitter> emitter, std::string fileName)
{
	ALuint buffer = LoadFile(fileName);
	ALuint source = m_Source[emitter.get()];
	alSourcei(source, AL_BUFFER, buffer);
	alSourcePlay(m_Source[emitter.get()]);
}

void Systems::SoundSystem::OnComponentCreated(std::string type, std::shared_ptr<Component> component)
{
	if(type == "SoundEmitter") {
		ALuint source = CreateSource();
		m_Source[component.get()] = source;
	}
}

ALuint Systems::SoundSystem::LoadFile(std::string fileName)
{
	if (m_BufferCache.find(fileName) != m_BufferCache.end())
		return m_BufferCache[fileName];

	FILE *fp = NULL;
	fp = fopen(fileName.c_str(), "rb");

	//CHECK FOR VALID WAVE-FILE
	fread(type, sizeof(char), 4, fp);
	if(type[0]!='R' || type[1]!='I' || type[2]!='F' || type[3]!='F') {
		LOG_ERROR("ERROR: No RIFF in WAVE-file");
		return 0;
	}

	fread(&size, sizeof(unsigned long), 1, fp);
	fread(type, sizeof(char), 4, fp);
	if(type[0]!='W' || type[1]!='A' || type[2]!='V' || type[3]!='E') {
		LOG_ERROR("ERROR: Not WAVE-file");
		return 0;
	}

	fread(type, sizeof(char), 4, fp);
	if(type[0]!='f' || type[1]!='m' || type[2]!='t' || type[3]!=' ') {
		LOG_ERROR("ERROR: No fmt in WAVE-file");
		return 0;
	}

	//READ THE DATA FROM WAVE-FILE
	fread(&chunkSize, sizeof(unsigned long), 1, fp);
	fread(&formatType, sizeof(short), 1, fp);
	fread(&channels, sizeof(short), 1, fp);
	fread(&sampleRate, sizeof(unsigned long), 1, fp);
	fread(&avgBytesPerSec, sizeof(unsigned long), 1, fp);
	fread(&bytesPerSample, sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if(type[0]!='d' || type[1]!='a' || type[2]!='t' || type[3]!='a')
	{
		LOG_ERROR("ERROR: WAVE-file Missing data");
		return 0;
	}

	fread(&dataSize, sizeof(unsigned long), 1, fp);

	unsigned char* buf = new unsigned char[dataSize];
	fread(buf, sizeof(unsigned char), dataSize, fp);
	fclose(fp);

	// Create buffer
	ALuint format = 0;
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

	ALuint buffer;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, buf, dataSize, sampleRate);
	delete[] buf;

	m_BufferCache[fileName] = buffer;
	return buffer;
}

ALuint Systems::SoundSystem::CreateSource()
{
	ALuint source;
	alGenSources((ALuint)1, &source);

	return source;
}