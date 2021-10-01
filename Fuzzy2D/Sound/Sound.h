//
//  Sound.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include <SDL_mixer.h>
#include <string>

struct SoundAssetInfo;

//Each SoundChannel corresponds with a specific SDL_Mixer channel to play sounds on
enum class SoundChannel
{
	ANY = -1, //Uses the first available channel
	BACKGROUND_MUSIC,
	PLAYER_SOUND_EFFECT,
	NEUTRAL_SOUND_EFFECT,
	INTERFACE_SOUND_EFFECT,
	ENEMY_SOUND_EFFECT,
};

//Represents a single game Sound. Can be either music (Mix_Music) or a sound effect (Mix_Chunk)
class Sound
{
public:
	Sound(const SoundChannel& channel, const std::string& fileName, const float& volume, const int& loops = 0);
	Sound(const SoundAssetInfo& info);
	~Sound();

	union {
		Mix_Music* _Song;
		Mix_Chunk* _Fx;
	};
	const SoundChannel _ChannelType;
	const float _Volume = 1.0;
	const int _Loops = 0;
};