#include "PCInputController.h"

#include <SDL_events.h>

/*
    Description:
        Constructs the mappings between the system agnostic InputEvents and the key codes
        that are specific to Mouse & Keyboard controls
*/
PCInputController::PCInputController()
{
    /* New InputEvents should be mapped here in order to get input data */

    _eventKeyMapping.insert({InputEvent::ACTION, SDLK_SPACE });
    _eventKeyMapping.insert({ InputEvent::BACK, SDLK_BACKSPACE });
    _eventKeyMapping.insert({ InputEvent::START, SDLK_KP_ENTER });
    _eventKeyMapping.insert({ InputEvent::QUIT, SDLK_ESCAPE });
    _eventKeyMapping.insert({ InputEvent::RESTART, SDLK_r });

    _eventMouseMapping.insert({ InputEvent::SHOOT, SDL_BUTTON_LEFT });
    _eventMouseMapping.insert({ InputEvent::BEAM, SDL_BUTTON_RIGHT });
}

/*
    Description:
        Update the given reference bool with the up to date input status for the given InputEvent.
        The event may require different types of polling, so we check if it's part of a specific mapping group
        or is a special case.

    Argument:
       eventMarker - Pass by Ref bool being updated. Likely a part of the current _inputState
       inputEvent - The event type we are being asked to poll
       polledSDLEvent - The event info give to us by SDLs event queue

    Return:
		bool& - Updated to true if the event is "active" and false if the event has be "deactivated". Usually this means a button has been pressed or released
*/
void PCInputController::UpdateEventStatus(bool& eventMarker, const InputEvent& inputEvent, const SDL_Event& polledSDLEvent)
{
    if (_eventKeyMapping.find(inputEvent) != _eventKeyMapping.end())
    {
        if (KeyCodePressed(_eventKeyMapping[inputEvent], polledSDLEvent))
            eventMarker = true;
        else if (KeyCodeReleased(_eventKeyMapping[inputEvent], polledSDLEvent))
            eventMarker = false;
    }
    else if (_eventMouseMapping.find(inputEvent) != _eventMouseMapping.end())
    {
        UpdateMouseEventStatus(eventMarker, _eventMouseMapping[inputEvent], polledSDLEvent);
    }
    else if (inputEvent == InputEvent::DIRECTION)
        UpdateDirectionalInputs(polledSDLEvent);

}

/*
    Description:
        Mouse events require specific button checks.

    Argument:
       eventMarker - Pass by Ref bool being updated. Likely a part of the current _inputState
       SDL_MOUSE_BUTTON - typedef in representing a specific mouse button
       polledSDLEvent - The event info give to us by SDLs event queue

    Return:
        bool& - eventMarker is returned updated  If the supplied button is pressed down,
        eventMarker is marked true. Otherwise if the button has been specifically released, eventMarker is marked false.
        IF neither are true, eventMarker is left unchanged (the case where a button is held down so the event is neither
        pressed nor released)
*/
void PCInputController::UpdateMouseEventStatus(bool& eventMarker, const int& SDL_MOUSE_BUTTON, const SDL_Event& polledSDLEvent)
{
    if (polledSDLEvent.type == SDL_MOUSEBUTTONDOWN)
    {
        if (polledSDLEvent.button.button == SDL_MOUSE_BUTTON)
        {
            eventMarker = true;
        }
    }
    else if (polledSDLEvent.type == SDL_MOUSEBUTTONUP)
    {
        if (polledSDLEvent.button.button == SDL_MOUSE_BUTTON)
        {
            eventMarker = false;
        }
    }
}

/*
    Description:
        Asks SDL for the current Mouse state. Updates vectorMarker to match.

    Return:
        vectorMarker& - Pass by referenced. Updated to hold the latest mouse information in screen coordinates
*/
void PCInputController::UpdateCursorPosition(Vector2& vectorMarker)
{
    int xPos = 0, yPos = 0;
    SDL_GetMouseState(&xPos, &yPos);

    vectorMarker.x = xPos;
    vectorMarker.y = yPos;
}

/*
    Description:
        Using the information gathered during the DIRECTION polling events to determine
        what direction the Player is heading towards. 

    Return:
        vectorMarker& - Pass by referenced. Updated to hold the latest movement direction. 0,-1 is North, 1,0 East, 0,1 South, -1,0 West
*/
void  PCInputController::UpdateMovementDirection(Vector2& vectorMarker)
{
    vectorMarker = Vector2(_isPressingHorizontalDirection, _isPressingVerticalDirection);
    if (_currentHorizontalDirection == Direction::LEFT)
        vectorMarker.x *= -1;
    if (_currentVerticalDirection == Direction::UP)
        vectorMarker.y *= -1;
}


/*
    Description:
        Helper function to check if a given keyCode is pressed
*/
bool PCInputController::KeyCodePressed(const SDL_Keycode& keyCode, const SDL_Event& polledSDLEvent) const
{
    if (polledSDLEvent.type == SDL_KEYDOWN)
    {
        if (polledSDLEvent.key.keysym.sym == keyCode)
        {
            return true;
        }
    }

    return false;
}

/*
    Description:
        Helper function to check if a given keyCode is Released
*/
bool PCInputController::KeyCodeReleased(const SDL_Keycode& keyCode, const SDL_Event& polledSDLEvent) const
{
    if (polledSDLEvent.type == SDL_KEYUP)
    {
        if (polledSDLEvent.key.keysym.sym == keyCode)
        {
            return true;
        }
    }

    return false;
}

/*
    Description:
        Helper function to set an index in the _activateDirections array to true based on the given Direction
*/
void PCInputController::ActivateDirection(Direction dir)
{
    if (dir == Direction::DOWN)
        _activeDirections.at(CommonHelpers::DirectionIndex(Direction::DOWN)) = true;
    else if (dir == Direction::LEFT)
        _activeDirections.at(CommonHelpers::DirectionIndex(Direction::LEFT)) = true;
    else if (dir == Direction::RIGHT)
        _activeDirections.at(CommonHelpers::DirectionIndex(Direction::RIGHT)) = true;
    else if (dir == Direction::UP)
        _activeDirections.at(CommonHelpers::DirectionIndex(Direction::UP)) = true;
}

/*
    Description:
        Helper function to set an index in the _activateDirections array to false based on the given Direction
*/
void PCInputController::ReleaseDirection(Direction dir)
{
    if (dir == Direction::DOWN)
        _activeDirections.at(CommonHelpers::DirectionIndex(Direction::DOWN)) = false;
    else if (dir == Direction::LEFT)
        _activeDirections.at(CommonHelpers::DirectionIndex(Direction::LEFT)) = false;
    else if (dir == Direction::RIGHT)
        _activeDirections.at(CommonHelpers::DirectionIndex(Direction::RIGHT)) = false;
    else if (dir == Direction::UP)
        _activeDirections.at(CommonHelpers::DirectionIndex(Direction::UP)) = false;
}

/*
    Description:
		A directional switchboard. 
        Turns on/off directional information in _activateDirections based on the given polling information.
        Survey's which directions are active to determine the dominate direction that a player is facing
*/
void PCInputController::UpdateDirectionalInputs(const SDL_Event& polledSDLEvent)
{
    if (KeyCodePressed(SDLK_a, polledSDLEvent))
        ActivateDirection(Direction::LEFT);
    else if (KeyCodePressed(SDLK_d, polledSDLEvent))
        ActivateDirection(Direction::RIGHT);
    else if (KeyCodePressed(SDLK_w, polledSDLEvent))
        ActivateDirection(Direction::UP);
    else if (KeyCodePressed(SDLK_s, polledSDLEvent))
        ActivateDirection(Direction::DOWN);
    else if (KeyCodeReleased(SDLK_a, polledSDLEvent))
        ReleaseDirection(Direction::LEFT);
    else if (KeyCodeReleased(SDLK_d, polledSDLEvent))
        ReleaseDirection(Direction::RIGHT);
    else if (KeyCodeReleased(SDLK_w, polledSDLEvent))
        ReleaseDirection(Direction::UP);
    else if (KeyCodeReleased(SDLK_s, polledSDLEvent))
        ReleaseDirection(Direction::DOWN);

    if (_activeDirections.at(CommonHelpers::DirectionIndex(Direction::DOWN)) || _activeDirections.at(CommonHelpers::DirectionIndex(Direction::UP)))
    {
        _isPressingVerticalDirection = true;
        if (_activeDirections.at(CommonHelpers::DirectionIndex(Direction::DOWN)))
            _currentVerticalDirection = Direction::DOWN;
        else
            _currentVerticalDirection = Direction::UP;
    }
    else
        _isPressingVerticalDirection = false;

    if (_activeDirections.at(CommonHelpers::DirectionIndex(Direction::LEFT)) || _activeDirections.at(CommonHelpers::DirectionIndex(Direction::RIGHT)))
    {
        _isPressingHorizontalDirection = true;
        if (_activeDirections.at(CommonHelpers::DirectionIndex(Direction::LEFT)))
            _currentHorizontalDirection = Direction::LEFT;
        else
            _currentHorizontalDirection = Direction::RIGHT;
    }
    else
        _isPressingHorizontalDirection = false;
}