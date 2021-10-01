//
//  SystemInputController.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "InputState.h"
#include <SDL.h>

/*
	ABC meant to abstract the InputManager from the system specific event polling requirements.
	New controller input types and systems will likely require their own derived implementation of this class
*/
class SystemInputController
{
public:
	virtual void UpdateEventStatus(bool& eventMarker, const InputEvent& inputEvent, const SDL_Event& polledSDLEvent) = 0;
	virtual void UpdateCursorPosition(Vector2& vectorMarker) = 0;
	virtual void UpdateMovementDirection(Vector2& vectorMarker) = 0;

};