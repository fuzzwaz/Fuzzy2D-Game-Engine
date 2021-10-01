//
//  SystemInputController.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Common.h"
#include "SystemInputController.h"

#include <SDL_keycode.h>
#include <unordered_map>


/*
	Input gathering for Mouse and Keyboard events specifically
*/
class PCInputController : public SystemInputController
{
public:
	PCInputController();

	void UpdateEventStatus(bool& eventMarker, const InputEvent& inputEvent, const SDL_Event& polledSDLEvent) override;
	void UpdateCursorPosition(Vector2& vectorMarker) override;
	void UpdateMovementDirection(Vector2& vectorMarker) override;

private:
	bool KeyCodePressed(const SDL_Keycode& keyCode, const SDL_Event& polledSDLEvent) const;
	bool KeyCodeReleased(const SDL_Keycode& keyCode, const SDL_Event& polledSDLEvent) const;

	void UpdateMouseEventStatus(bool& eventMarker, const int& SDL_MOUSE_BUTTON, const SDL_Event& polledSDLEvent);

	void ActivateDirection(Direction dir);
	void ReleaseDirection(Direction dir);
	void UpdateDirectionalInputs(const SDL_Event& polledSDLEvent);

	
	std::vector<bool> _activeDirections = { false, false, false, false }; //Uses to keep track of specifically which directional inputs are being pressed over time
	bool _isPressingVerticalDirection = false;
	bool _isPressingHorizontalDirection = false;
	Direction _currentVerticalDirection = Direction::DOWN; //Determines the dominate directions even when multiple directions may be active
	Direction _currentHorizontalDirection = Direction::LEFT; //Determines the dominate directions even when multiple directions may be active

	std::unordered_map<InputEvent, SDL_Keycode> _eventKeyMapping; //Which Events correspond with specific Keyboard keys
	std::unordered_map<InputEvent, int> _eventMouseMapping; //Which Events correspond with specific Mouse Buttons

};
