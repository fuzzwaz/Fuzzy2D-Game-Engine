//
//  main.cpp
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#include "Common.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Timer.h"

#include <algorithm>
#include <memory>


int main( int argc, char* args[] )
{
    std::unique_ptr<GameManager> mainGame(new GameManager());
    mainGame->Initialize();

    const int MS_PER_FRAME = 1000 / DESIRED_UPDATES_PER_SECOND;

    Timer gameTime;
    gameTime.Start();

    double previous = gameTime.GetMilliseconds();
    double lag = 0.0;

    bool quit = false;
    InputManager playerInput;
    while (!quit)
    {
        const double current = gameTime.GetMilliseconds();
        const double elapsed = current - previous;
        previous = current;
        lag += elapsed;

        const InputState input = playerInput.PollPlayerInput();
        quit = input._QuitPressed;

        /*
            In the situation that the game is running behind the desired FPS,
            update the non rendering related game logic until the game catches up
        */
        while (lag >= MS_PER_FRAME)
        {
            mainGame->Update(input);
            lag -= MS_PER_FRAME;
        }
        lag = std::max(lag, 0.0);

        mainGame->Render();
    }

    mainGame->QuitGame();
    
    return 0;
}
