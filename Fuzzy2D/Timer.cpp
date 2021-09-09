
#include "Timer.h"

void Timer::Start()
{
    _active = true;
    _millisecondsSinceStarting = SDL_GetTicks(); //Gets the # of MS passed since game start
}

void Timer::Stop()
{
    _active = false;
}

Uint32 Timer::GetMilliseconds() const
{
    if (_active)
        return SDL_GetTicks() - _millisecondsSinceStarting; //Total MS since game start minus the MS that has passed at the time that the timer was started

    return 0;
}

float Timer::GetSeconds() const
{
    return GetMilliseconds() / 1000.0; //1000 MS in a Second
}
