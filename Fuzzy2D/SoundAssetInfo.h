//
//  SoundAssetInfo.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Sound.h"

//Used to represent a Sound Asset to be initialized at some future point
struct SoundAssetInfo
{
	SoundAssetInfo(const std::string& filePath, const SoundChannel& channel = SoundChannel::ANY, const float& volume = 1, const int& loops = 0) :
	_FilePath(filePath), _Channel(channel), _Volume(volume), _Loops(loops) { }

	std::string _FilePath;
	SoundChannel _Channel;
	float _Volume;
	int _Loops;

};