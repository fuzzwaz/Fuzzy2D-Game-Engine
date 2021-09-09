//
//  InputState.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Vector2.h"

//The Events which are associated with input data that needs to be polled.
//Consumed by SystemInputControllers to determine how they will specifically poll an event for the system
enum InputEvent { ACTION, BACK, START, QUIT, SHOOT, RESTART, BEAM, DIRECTION };

/*
	An informational struct meant to represent a snapshot of input information.
	Agnostic of system specific implementation details (Keyboard/controller for example).

	This will be unique to each game and must be updated to represent the events being tracked
*/
struct InputState {
	bool _ActionPressed = false;
	bool _BackPressed = false;
	bool _StartPressed = false;
	bool _QuitPressed = false;
	bool _ShootPressed = false;
	bool _RestartPressed = false;
	bool _BeamPressed = false;

	Vector2 _CursorPosition = Vector2(0, 0);
	Vector2 _MovementDirection = Vector2(0, 0);
};