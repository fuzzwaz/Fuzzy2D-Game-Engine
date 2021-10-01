//
//  Animator.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Animation.h"

/*
	Animation controller of sorts. Keeps track of the current animation and which frame within that animation should be active.
	The connective tissue between the GraphicsController (which renders the animation) and the Animations themselves
*/
class Animator
{
public:
	Animator(PropertyController* propertyController);

	void operator=(const Animator& source);

	void Update();
	void Play() const;
	void Stop() const;

	void SetCurrentAnimation(const std::shared_ptr<const Animation>& animation);
	void SetAnimationFramePercent(const float& percent) const; //0% is the first frame. 100% is the last frame

	std::shared_ptr<Texture> GetCurrentFrame() const { return _currentAnim->GetCurrentFrame(_frameIndex); }

private:
	void TransitionToNextAnimationIfNeeded();
	void UpdateCurrentFrameBasedOnCurrentTime() const;

	std::shared_ptr<const Animation> _currentAnim = nullptr; 
	std::shared_ptr<const Animation> _startingAnim = nullptr;
	PropertyController* _propertyController = nullptr; //Associated set of properties which dictates animation transitions

	const int _timePerFrame = 200; //How many MS are spent on each frame

	/* These properties are mutable because an Animation should be able to play while being const */
	mutable int _frameIndex = 0; //Current frame that the animator is working with within the current animation (_currentAnim)
	mutable bool _playing = false; //If the animation is actively progressing frames or paused
	mutable Timer _clock; //The timer which dictates animation progression
};
