#include "Animation.h"
#include "GraphicAssetInfo.h"

#include <algorithm>

using std::shared_ptr;
using std::vector;

Animation::Animation(const GraphicAssetInfo& animInfo) : _speed(animInfo._AnimationSpeed) , _looping(animInfo._Looping), _flipType(animInfo._FlipStyle), _timerBased(!animInfo._PercentageBased)
{
	Texture::LoadTextures(_frames, animInfo);
}

Animation::Animation(const Animation& source) : _speed(source._speed), _looping(source._looping), _flipType(source._flipType), _timerBased(source._timerBased)
{
	_frames.insert(_frames.end(), source._frames.cbegin(), source._frames.cend());
}

Animation::~Animation()
{
	std::for_each(_frames.begin(), _frames.end(), [](shared_ptr<Texture>& frame) {frame.reset();});
	_frames.clear();
}

void Animation::AddFrame(const shared_ptr<Texture>& texture)
{
	_frames.push_back(texture);
}

void Animation::AddTransition(const Transition& transition)
{
	_transitions.push_back(transition);
}

/*
	Description:
		Checks to see if a transition already exists for the given destination. If so, adds the property value pair
		to the preexisting transition. Otherwise, creates a new transition and adds it to _transitions.
*/
void Animation::AddTransition(const Property& propertyId, const int& value, const shared_ptr<const Animation>& destination)
{
	for (Transition& ts : _transitions)
	{
		if (ts.GetDestination() == destination)
		{
			ts.AddProperty(propertyId, value);
			return;
		}
	}

	this->AddTransition(Transition(propertyId, value, destination));
}

shared_ptr<Texture> Animation::GetCurrentFrame(int frameIndex) const
{
	if (!_looping && frameIndex >= _frames.size()) //If not looping, the animation ends once the last frame is complete
	{
		return nullptr; //Returning nullptr tells the graphics controller not to display any textures
	}

	frameIndex = frameIndex % _frames.size();
	return _frames[frameIndex];
}

/*
	Description:
		Checks if any of the transition's property expectations have been matched. If so, return that transition's
		animation destination. Otherwise, return nullptr to represent no change in animation.

	Arguments:
		frameIndex - The index for the current frame that is activate in the animation
		propertyController - A list of properties for a given object
*/
shared_ptr<const Animation> Animation::GetNextAnimation(const int& frameIndex, const PropertyController* propertyController) const
{
	for (const auto& transition : _transitions)
	{
		if (!_looping)
		{
			//Non-looping animations don't transition until all of their frame's have executed 
			const bool shouldTransition = transition.ShouldTransition(*propertyController) && frameIndex >= _frames.size() - 1;
			if (shouldTransition)
				return transition.GetDestination();
		}
		else if (_looping)
		{
			const bool shouldTransition = transition.ShouldTransition(*propertyController);
			if (shouldTransition)
				return transition.GetDestination();
		}
	}
	return nullptr;
}