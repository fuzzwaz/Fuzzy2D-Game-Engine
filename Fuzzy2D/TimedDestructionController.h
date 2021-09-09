//
//  TimedDestructionController.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Timer.h"
#include "ObserverController.h"

/*
	A controller meant to attach to GameObjects that should be destroyed after a certain amount of time. A fairly common behavioral script.
	GameObjects pass in their observers so that the controller can handle the destruction process entirely by alerting the
	GameManager that said object should be destroyed on the next frame.
*/
class TimedDestructionController
{
public:
	TimedDestructionController(const ObserverController& observers, const float& time = -1) : _observerController(observers), _destructionTime(time) {}

	bool TimeIsUp();

	void SetDestructionTime(const float& time) { _destructionTime = time; }

	void operator=(const TimedDestructionController& source);

private:
	bool _destroyed = false; //True when _destructionTime has elapsed 
	float _destructionTime = -1; //The time until destruction. -1 is the default and means that the destruction countdown will not activate
	Timer _destructionTimer;

	const ObserverController& _observerController; //The observerController for the object being destroyed
};
