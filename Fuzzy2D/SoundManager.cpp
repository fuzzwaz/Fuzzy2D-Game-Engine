#include "ErrorHandler.h"
#include "SoundManager.h"
#include "SoundAssetResources.h"

#include <SDL_mixer.h>

/*
	Description:
		Sets and confirms that the SDL_Mixer audio system is working.
		Required before constructing/initializing any sound objects
*/
SoundManager::SoundManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		ErrorHandler::Assert(true, "Sound Manager failed to initialized");
	}

	CreateSoundEffectMappings();
}

SoundManager::~SoundManager()
{
	_soundEffectEventMap.clear();
}

void SoundManager::PlaySound(const std::shared_ptr<const Sound>& sound) const
{
	SetChannelVolume(sound->_ChannelType, sound->_Volume);

	if (sound->_ChannelType == SoundChannel::BACKGROUND_MUSIC)
	{
		Mix_PlayMusic(sound->_Song, sound->_Loops);
	}
	else
	{
		Mix_PlayChannel(static_cast<int>(sound->_ChannelType), sound->_Fx, sound->_Loops);
	}
	
}

void SoundManager::StopChannel(const SoundChannel& channel) const
{
	Mix_Pause(static_cast<int>(channel));
}

/*
	Description:
		Sets the volume on a specific audio channel

	Arguments:
		channel - The channel for which the volume is being adjusted
		volume - 0 means no volume. 1 means full volume.
*/
void SoundManager::SetChannelVolume(const SoundChannel& channel, float volume /*0 to 1*/) const
{
	if (volume > 1)
		volume = 1;
	else if (volume < 0)
		volume = 0;
	
	if (channel == SoundChannel::BACKGROUND_MUSIC)
	{
		Mix_VolumeMusic(MIX_MAX_VOLUME * volume);
	}
	else
	{
		Mix_Volume(static_cast<int>(channel), MIX_MAX_VOLUME * volume);
	}
}

/*
	Description:
		Plays the appropriate sound according the the given Event

	Arguments:
		eventType - The Event currently being dealt. Used as a key for the "_soundEffectEventMap"
*/
void SoundManager::Notify(const GameObjectEvent& eventType)
{
	const auto foundMatchingSound = _soundEffectEventMap.find(eventType);

	if (foundMatchingSound != _soundEffectEventMap.end())
	{
		PlaySound(foundMatchingSound->second);

		if (eventType == GameObjectEvent::GAME_OVER || eventType == GameObjectEvent::VICTORY)
			StopPlayingAllSoundEffects();
	}
}

/*
	Description:
		Initializes all of the sound effects and pairs them with their corresponding
		GameObjectEvents within the "_soundEffectEventMap." 
*/
void SoundManager::CreateSoundEffectMappings()
{
	/* Map Your Events to Sound Effects Here */
}

void SoundManager::StopPlayingAllSoundEffects() const
{
	StopChannel(SoundChannel::PLAYER_SOUND_EFFECT);
	StopChannel(SoundChannel::NEUTRAL_SOUND_EFFECT);
	StopChannel(SoundChannel::INTERFACE_SOUND_EFFECT);
	StopChannel(SoundChannel::ENEMY_SOUND_EFFECT);
}