//
//  Animation.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Texture.h"
#include "Timer.h"
#include "Transition.h"
#include "PropertyController.h"

#include <vector>
#include <memory>

/*
	An ordered list of Texture objects with added information about how to move from one texture to the next.
	Acts as a node in a animation graph. Has Transitions to other animations in the graph.
 */
class Animation
{
public:
	Animation(const GraphicAssetInfo& animInfo);
	Animation(const Animation& source);
	~Animation();

	void AddFrame(const std::shared_ptr<Texture>& texture);

	void AddTransition(const Transition& transition);
	void AddTransition(const Property& propertyId, const int& value, const std::shared_ptr<const Animation>& destination);

	std::shared_ptr<const Animation> GetNextAnimation(const int& frameIndex, const PropertyController* propertyController) const;

	/* Getters */
	bool IsTimerBased() const { return _timerBased; } //Whether an the Animation progresses over time or when told to do so
	bool IsLooping() const { return _looping; } //Whether the animation loops back to the first frame after the last
	float GetAnimationSpeed() const { return _speed; } //Speeds or slows down the animator. 1.0 is the default animator speed
	int GetFrameCount() const { return _frames.size(); }
	SDL_RendererFlip GetFlipSetting() const { return _flipType; } //Whether the animation should be flipped while rendering
	std::shared_ptr<Texture> GetCurrentFrame(int frameIndex) const;

private:
	bool _timerBased = true;
	bool _looping = true;
	float _speed = 1.0f;
	SDL_RendererFlip _flipType = SDL_FLIP_NONE;

	std::vector<std::shared_ptr<Texture>> _frames;
	std::vector<Transition> _transitions;
};
