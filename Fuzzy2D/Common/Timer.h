//
//  Timer.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//

#pragma once

#include <SDL.h>

//Basic Timer helper class which can return elapsed game time seconds since being started
class Timer
{
public:
    Timer() = default;

    void Start();
    void Stop();

    /* Getters */
    Uint32 GetMilliseconds() const;
    float GetSeconds() const;
    bool GetActive() const { return _active; }
    
private:
    Uint32 _millisecondsSinceStarting = 0; //How many MS have passed since "Start" was called
    bool _active = false;
};
