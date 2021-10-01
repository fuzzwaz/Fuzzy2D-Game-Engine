//
//  SoundManager.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "GameObjectObserver.h"
#include "Sound.h"

#include <memory>
#include <unordered_map>

//Initializes and manages all game sounds. Responses to gameplay events by playing the appropriately associated sound
class SoundManager : public GameObjectObserver
{
public:
	SoundManager();
	virtual ~SoundManager();

	void PlaySound(const std::shared_ptr<const Sound>& sound) const;
	void StopChannel(const SoundChannel& channel) const;
	void SetChannelVolume(const SoundChannel& channel, float volume /*0 to 1*/) const;

	void Notify(const GameObjectEvent& eventType) override;

private:
	void CreateSoundEffectMappings();
	void StopPlayingAllSoundEffects() const;

	std::unordered_map<GameObjectEvent, std::shared_ptr<const Sound>> _soundEffectEventMap;
};
