#include "InputManager.h"
#include "PCInputController.h"

InputManager::InputManager()
{
    _inputController = std::make_unique<PCInputController>(); //By default, we are using the PC Mouse & Keyboard controllers
}

/*
    Description:
        Empties the SDL event queue and asks the current _inputController to react to the event by updating _inputState.
        Returns a copy of _inputState for the rest of the engine/
    
    Return:
        InputState - A copy of the internal _inputState. Up to date information of the polled input events from the current frame
*/
InputState InputManager::PollPlayerInput()
{
    while (SDL_PollEvent(&_polledSDLEvent))
    {
        bool directionEvent; //Not required for Direction events
        _inputController->UpdateEventStatus(directionEvent, InputEvent::DIRECTION, _polledSDLEvent);
        _inputController->UpdateEventStatus(_inputState._ActionPressed, InputEvent::ACTION, _polledSDLEvent);
        _inputController->UpdateEventStatus(_inputState._BackPressed, InputEvent::BACK, _polledSDLEvent);
        _inputController->UpdateEventStatus(_inputState._StartPressed, InputEvent::START, _polledSDLEvent);
        _inputController->UpdateEventStatus(_inputState._QuitPressed, InputEvent::QUIT, _polledSDLEvent);
        _inputController->UpdateEventStatus(_inputState._RestartPressed, InputEvent::RESTART, _polledSDLEvent);
        _inputController->UpdateEventStatus(_inputState._ShootPressed, InputEvent::SHOOT, _polledSDLEvent);
        _inputController->UpdateEventStatus(_inputState._BeamPressed, InputEvent::BEAM, _polledSDLEvent);
    }

    _inputController->UpdateCursorPosition(_inputState._CursorPosition); //Rename to _Cursor
    _inputController->UpdateMovementDirection(_inputState._MovementDirection);

    return _inputState;
}