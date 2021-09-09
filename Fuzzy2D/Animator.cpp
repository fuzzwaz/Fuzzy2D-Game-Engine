#include "Animator.h"
#include "ErrorHandler.h"

using std::shared_ptr;

Animator::Animator(PropertyController* propertyController) : _propertyController(propertyController)
{
	ErrorHandler::Assert(propertyController != nullptr, "_propertyController has been set to nullptr");
}

void Animator::operator=(const Animator& source)
{
	if (this == &source)
		return;

	*_propertyController = *source._propertyController;
	SetCurrentAnimation(source._startingAnim);
}

void Animator::SetCurrentAnimation(const std::shared_ptr<const Animation>& animation)
{
	if (_startingAnim == nullptr)
		_startingAnim = animation;

	_currentAnim = animation;
	_frameIndex = 0;
	Play();
}

void Animator::Play() const
{
	if (!_playing)
	{
		_playing = true;
		_clock.Start();
	}
}

void Animator::Stop() const
{
	_playing = false;
	_clock.Stop();
}

/*
	Description:
		Called whenever the graphics on an object should be progressed forward (typically every frame).
		In charge of updating timer based animation frames and transitioning to the next appropriate
		Animation.
*/
void Animator::Update()
{
	ErrorHandler::Assert(_currentAnim != nullptr, "Animator does not have a Current Animation set");
	if (_currentAnim == nullptr)
		return;

	TransitionToNextAnimationIfNeeded();

	if (_currentAnim->IsTimerBased())
		UpdateCurrentFrameBasedOnCurrentTime();
}

/*
	Description:
		Asks the current animation if it is ready to transition to the next.
		If so, transitions by stopping the old and starting the new.
*/
void Animator::TransitionToNextAnimationIfNeeded()
{
	const shared_ptr<const Animation> nextAnim = _currentAnim->GetNextAnimation(_frameIndex, _propertyController);
	if (nextAnim != nullptr)
	{
		Stop();
		SetCurrentAnimation(nextAnim);
	}
}

/*
	Description:
		For timer based Animations, updates the _frameIndex based on how much time has passed since
		the last update call.
*/
void Animator::UpdateCurrentFrameBasedOnCurrentTime() const
{
	if (_playing)
	{
		const bool FrameTimeHasElapsed = _clock.GetMilliseconds() >= _timePerFrame / _currentAnim->GetAnimationSpeed();
		if (FrameTimeHasElapsed)
		{
			/* Progress to the next frame */
			_frameIndex++;

			/* Check if we are done playing the Animation (Non looping) */
			const bool FinalFrameHasPlayed = _frameIndex >= _currentAnim->GetFrameCount() && !_currentAnim->IsLooping();
			if (FinalFrameHasPlayed)  //Only non looping animations have "final frames"
			{
				_frameIndex = _currentAnim->GetFrameCount();
				Stop();
				return;
			}

			/* Deal with frameIndex overflow and reset the animation clock */
			_frameIndex %= _currentAnim->GetFrameCount();
			_clock.Start();
		}
	}
}

/*
	Description:
		For percent based Animations, updates the _frameIndex based on the given percent value.
		0% is the first frame. 100% is the last frame.
*/
void Animator::SetAnimationFramePercent(const float& percent) const
{
	ErrorHandler::Assert(_currentAnim != nullptr, "Animator does not have a Current Animation set");
	if (_currentAnim == nullptr)
		return;

	if (!_currentAnim->IsTimerBased())
	{
		//Get the frame for the given percent value
		int frame = (percent / 100.0) * (_currentAnim->GetFrameCount() - 1);

		//Deal with wrapping in case the percent value was invalid
		if (frame < 0)
			frame = 0;
		else if (frame >= _currentAnim->GetFrameCount())
			frame = _currentAnim->GetFrameCount() - 1;

		//Set the next frame
		_frameIndex = frame;
	}
}
