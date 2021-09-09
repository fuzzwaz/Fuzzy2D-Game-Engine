//
//  InputManager.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "SystemInputController.h"

#include <memory>

/*
	Manages SystemInputControllers which are responsible for polling different system types for up to date input information.
	Takes the up to date information form the Controllers and sends them back to the GameManager via an InputState struct. 
*/
class InputManager
{
public:
	InputManager();
	//Polls for input events and returns a pointer to the InputState struct holding the relevant results of each poll.
	InputState PollPlayerInput();

private:
	SDL_Event _polledSDLEvent; //The current SDL event returned by the event queue. Must be processed by a SystemInputController
	InputState _inputState; //The current _inputState. A copy is sent to the rest of the engine each frame to react to
	std::unique_ptr<SystemInputController> _inputController = nullptr; //Which ever SystemInputController is set here will be the active input type. This is how you would change controller types (Keyboard vs Controller)
};
