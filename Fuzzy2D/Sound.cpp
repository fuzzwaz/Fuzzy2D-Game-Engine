#include "ErrorHandler.h"
#include "Sound.h"
#include "SoundAssetInfo.h"

Sound::Sound(const SoundChannel& channel, const std::string& fileName, const float& volume, const int& loops) : _ChannelType(channel), _Volume(volume), _Loops(loops)
{
	if (channel == SoundChannel::BACKGROUND_MUSIC)
	{
		_Song = Mix_LoadMUS(fileName.c_str());
		ErrorHandler::Assert(_Song != NULL, "Error loading song: " + fileName + ". Info: " + Mix_GetError());
			
	}
	else
	{
		_Fx = Mix_LoadWAV(fileName.c_str());
		ErrorHandler::Assert(_Fx != NULL, "Error loading sound fx: " + fileName + ". Info: " + Mix_GetError());
	}
}

Sound::Sound(const SoundAssetInfo& info) : Sound(info._Channel, info._FilePath, info._Volume, info._Loops )
{
	
}

Sound::~Sound()
{
	if (_ChannelType == SoundChannel::BACKGROUND_MUSIC)
	{
		Mix_FreeMusic(_Song);
		_Song = nullptr;
	}
	else
	{
		Mix_FreeChunk(_Fx);
		_Fx = nullptr;
	}
}