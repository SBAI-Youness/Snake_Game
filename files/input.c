#include "../headers/input.h"
#include "../headers/game_logic.h"

void HandleMenuInput()
{
    // Event handling loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Handle each event type
        switch (event.type)
        {
            // If the user quits the game
            case SDL_QUIT:
                quit = true;
                break;

            // If a key is pressed
            case SDL_KEYDOWN:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle keyboard input
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            if (isHovering == onStart)
                                isHovering = onExit;
                            else if (isHovering == onExit)
                                isHovering = onStart;
                            else
                                isHovering = onStart;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_DOWN:
                            if (isHovering == onStart)
                                isHovering = onExit;
                            else if (isHovering == onExit)
                                isHovering = onStart;
                            else
                                isHovering = onExit;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_RETURN:
                            if (isHovering == onStart)
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MODE;
                            }
                            else if (isHovering == onExit)
                            {
                                MenuOption = EXIT;
                            }
                            break;
                    }
                }
                break;

            // This case is related to mouse motions
            case SDL_MOUSEMOTION:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Extract the x and y coordinates of the mouse pointer from the event
                    int mouseX = event.motion.x, mouseY = event.motion.y;

                    if (mouseX >= 280 && mouseX <= 500 && mouseY >= 150 && mouseY <= 230) // Mouse is hovering start button
                    {
                        if (isHovering != onStart)
                        {
                            isHovering = onStart;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if (mouseX >= 280 && mouseX <= 500 && mouseY >= 240 && mouseY <= 320) // Mouse is hovering exit button
                    {
                        if (isHovering != onExit)
                        {
                            isHovering = onExit;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else // Mouse is hovering any button
                        isHovering = onNothing;
                }
                break;

            // If a mouse button is released
            case SDL_MOUSEBUTTONUP:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle mouse input
                    switch (event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            int mouseX = event.button.x, mouseY = event.button.y;

                            if (mouseX >= 280 && mouseX <= 500 && mouseY >= 150 && mouseY <= 230) // If the user pressed start
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MODE;
                            }
                            else if (mouseX >= 280 && mouseX <= 500 && mouseY >= 240 && mouseY <= 320) // If the user pressed exit
                            {
                                MenuOption = EXIT;
                            }
                            break;
                    }
                }
                break;
        }
    }
}

void HandleModeInput()
{
    // Event handling loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Handle each event type
        switch (event.type)
        {
            // If the user quits the game
            case SDL_QUIT:
                quit = true;
                break;

            // If a key is pressed
            case SDL_KEYDOWN:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle keyboard input
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            if (isHovering == onMode1)
                                isHovering = onMode2;
                            else if (isHovering == onMode2)
                                isHovering = onMode1;
                            else
                                isHovering = onMode1;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_DOWN:
                            if (isHovering == onMode1)
                                isHovering = onMode2;
                            else if (isHovering == onMode2)
                                isHovering = onMode1;
                            else
                                isHovering = onMode2;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_RETURN:
                            if (isHovering == onMode1 || isHovering == onMode2)
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = START;
                            }
                            break;
                    }
                }
                break;

            // This case is related to mouse motions
            case SDL_MOUSEMOTION:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Extract the x and y coordinates of the mouse pointer from the event
                    int mouseX = event.motion.x, mouseY = event.motion.y;

                    if (mouseX >= 10 && mouseX <= 60 && mouseY >= 10 && mouseY <= 60) // Mouse is hovering the return button
                    {
                        if (isHovering != onReturn)
                        {
                            isHovering = onReturn;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if (mouseX >= 325 && mouseX <= 475 && mouseY >= 150 && mouseY <= 220) // Mouse is hovering the first mode
                    {
                        if (isHovering != onMode1)
                        {
                            isHovering = onMode1;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if (mouseX >= 325 && mouseX <= 475 && mouseY >= 240 && mouseY <= 310) // Mouse is hovering the second mode
                    {
                        if (isHovering != onMode2)
                        {
                            isHovering = onMode2;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else // Mouse is hovering any button
                        isHovering = onNothing;
                }
                break;

            // If a mouse button is released
            case SDL_MOUSEBUTTONUP:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle mouse input
                    switch (event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            int mouseX = event.button.x, mouseY = event.button.y;

                            if (mouseX >= 10 && mouseX <= 60 && mouseY >= 10 && mouseY <= 60) // Mouse is hovering the return button
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MENU;
                            }
                            else if (mouseX >= 325 && mouseX <= 475 && mouseY >= 150 && mouseY <= 220) // If the user pressed the first mode
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = START;
                            }
                            else if (mouseX >= 325 && mouseX <= 475 && mouseY >= 240 && mouseY <= 310) // If the user pressed the second mode
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = START;
                            }
                            break;
                    }
                }
                break;
        }
    }
}

void HandleMode1Input(player *snake)
{
    // ensuring that the direction can only be changed once per frame
    bool directionChanged = false;

    // Event handling loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Handle each event type
        switch (event.type)
        {
            // If the user quits the game
            case SDL_QUIT:
                quit = true;
                break;

            // If a key is pressed
            case SDL_KEYDOWN:
                if (directionChanged) break;

                // Handle keyboard input
                switch (event.key.keysym.sym)
                {
                    case SDLK_z:
                    case SDLK_UP:
                        if (snake->chunk[0].direction != DOWN)
                        {
                            snake->chunk[0].direction = UP;
                            snake->chunk[0].angle = -90;
                            directionChanged = true;
                        }
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        if (snake->chunk[0].direction != LEFT)
                        {
                            snake->chunk[0].direction = RIGHT;
                            snake->chunk[0].angle = 0;
                            directionChanged = true;
                        }
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        if (snake->chunk[0].direction != UP)
                        {
                            snake->chunk[0].direction = DOWN;
                            snake->chunk[0].angle = 90;
                            directionChanged = true;
                        }
                        break;
                    case SDLK_q:
                    case SDLK_LEFT:
                        if (snake->chunk[0].direction != RIGHT)
                        {
                            snake->chunk[0].direction = LEFT;
                            snake->chunk[0].angle = 180;
                            directionChanged = true;
                        }
                        break;
                }
                break;
        }
    } directionChanged = false;
}

void HandleMode2Input( player *snake1, player *snake2)
{
    // ensuring that the direction can only be changed once per frame
    bool direction1Changed = false, direction2Changed = false;

    // Event handling loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Handle each event type
        switch (event.type)
        {
            // If the user quits the game
            case SDL_QUIT:
                quit = true;
                break;

            // If a key is pressed
            case SDL_KEYDOWN:
                // Handle keyboard input
                switch (event.key.keysym.sym)
                {
                    // Input handling for the player number 1
                    case SDLK_UP:
                        if (!direction1Changed && snake1->chunk[0].direction != DOWN)
                        {
                            snake1->chunk[0].direction = UP;
                            snake1->chunk[0].angle = -90;
                            direction1Changed = true;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (!direction1Changed && snake1->chunk[0].direction != LEFT)
                        {
                            snake1->chunk[0].direction = RIGHT;
                            snake1->chunk[0].angle = 0;
                            direction1Changed = true;
                        }
                        break;
                    case SDLK_DOWN:
                        if (!direction1Changed && snake1->chunk[0].direction != UP)
                        {
                            snake1->chunk[0].direction = DOWN;
                            snake1->chunk[0].angle = 90;
                            direction1Changed = true;
                        }
                        break;
                    case SDLK_LEFT:
                        if (!direction1Changed && snake1->chunk[0].direction != RIGHT)
                        {
                            snake1->chunk[0].direction = LEFT;
                            snake1->chunk[0].angle = 180;
                            direction1Changed = true;
                        }
                        break;

                    // Input handling for the player number 2
                    case SDLK_z:
                        if (!direction2Changed && snake2->chunk[0].direction != DOWN)
                        {
                            snake2->chunk[0].direction = UP;
                            snake2->chunk[0].angle = -90;
                            direction2Changed = true;
                        }
                        break;
                    case SDLK_d:
                        if (!direction2Changed && snake2->chunk[0].direction != LEFT)
                        {
                            snake2->chunk[0].direction = RIGHT;
                            snake2->chunk[0].angle = 0;
                            direction2Changed = true;
                        }
                        break;
                    case SDLK_s:
                        if (!direction2Changed && snake2->chunk[0].direction != UP)
                        {
                            snake2->chunk[0].direction = DOWN;
                            snake2->chunk[0].angle = 90;
                            direction2Changed = true;
                        }
                        break;
                    case SDLK_q:
                        if (!direction2Changed && snake2->chunk[0].direction != RIGHT)
                        {
                            snake2->chunk[0].direction = LEFT;
                            snake2->chunk[0].angle = 180;
                            direction2Changed = true;
                        }
                        break;
                }
                break;
        }
    } direction1Changed = false; direction2Changed = false;
}

void HandleGameOverMode1Input()
{
    // Event handling loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Handle each event type
        switch (event.type)
        {
            // If the user quits the game
            case SDL_QUIT:
                quit = true;
                break;

            // If a key is pressed
            case SDL_KEYDOWN:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle keyboard input
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            if (isHovering != onPlayAgain)
                            {
                                isHovering = onPlayAgain;
                                Mix_PlayMusic( ClickingPopMusic, 0);
                            }
                            break;
                        case SDLK_LEFT:
                            if (isHovering != onHome)
                            {
                                isHovering = onHome;
                                Mix_PlayMusic( ClickingPopMusic, 0);
                            }
                            break;
                        case SDLK_RETURN:
                            if (isHovering == onHome || isHovering == onPlayAgain)
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = (isHovering == onHome)? MENU: (isHovering == onPlayAgain)? START: isHovering;
                            }
                            break;
                    }
                }
                break;

            // This case is related to mouse motions
            case SDL_MOUSEMOTION:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Extract the x and y coordinates of the mouse pointer from the event
                    int mouseX = event.motion.x, mouseY = event.motion.y;

                    if (mouseX >= 290 && mouseX <= 360 && mouseY >= 300 && mouseY <= 370) // Mouse is hovering home button
                    {
                        if (isHovering != onHome)
                        {
                            isHovering = onHome;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if (mouseX >= 440 && mouseX <= 510 && mouseY >= 300 && mouseY <= 370) // Mouse is hovering play again button
                    {
                        if (isHovering != onPlayAgain)
                        {
                            isHovering = onPlayAgain;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else // Mouse is hovering any button
                        isHovering = onNothing;
                }
                break;

            // If a mouse button is released
            case SDL_MOUSEBUTTONUP:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle mouse input
                    switch (event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            int mouseX = event.button.x, mouseY = event.button.y;

                            if (mouseX >= 290 && mouseX <= 360 && mouseY >= 300 && mouseY <= 370) // If the user pressed home
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MENU;
                            }
                            else if (mouseX >= 440 && mouseX <= 510 && mouseY >= 300 && mouseY <= 370) // If the user pressed play again
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = START;
                            }
                            break;
                    }
                }
                break;
        }
    }
}

void HandleGameOverMode2Input()
{
    // Event handling loop
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // Handle each event type
        switch (event.type)
        {
            // If the user quits the game
            case SDL_QUIT:
                quit = true;
                break;

            // If a key is pressed
            case SDL_KEYDOWN:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle keyboard input
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            if (isHovering != onPlayAgain)
                            {
                                isHovering = onPlayAgain;
                                Mix_PlayMusic( ClickingPopMusic, 0);
                            }
                            break;
                        case SDLK_LEFT:
                            if (isHovering != onHome)
                            {
                                isHovering = onHome;
                                Mix_PlayMusic( ClickingPopMusic, 0);
                            }
                            break;
                        case SDLK_RETURN:
                            if (isHovering == onHome || isHovering == onPlayAgain)
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = (isHovering == onHome)? MENU: (isHovering == onPlayAgain)? START: isHovering;
                            }
                            break;
                    }
                }
                break;

            // This case is related to mouse motions
            case SDL_MOUSEMOTION:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Extract the x and y coordinates of the mouse pointer from the event
                    int mouseX = event.motion.x, mouseY = event.motion.y;

                    if (mouseX >= 290 && mouseX <= 360 && mouseY >= 300 && mouseY <= 370) // Mouse is hovering home button
                    {
                        if (isHovering != onHome)
                        {
                            isHovering = onHome;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if (mouseX >= 440 && mouseX <= 510 && mouseY >= 300 && mouseY <= 370) // Mouse is hovering play again button
                    {
                        if (isHovering != onPlayAgain)
                        {
                            isHovering = onPlayAgain;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else // Mouse is hovering any button
                        isHovering = onNothing;
                }
                break;

            // If a mouse button is released
            case SDL_MOUSEBUTTONUP:
                if (!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle mouse input
                    switch (event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            int mouseX = event.button.x, mouseY = event.button.y;

                            if (mouseX >= 290 && mouseX <= 360 && mouseY >= 300 && mouseY <= 370) // If the user pressed home
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MENU;
                            }
                            else if (mouseX >= 440 && mouseX <= 510 && mouseY >= 300 && mouseY <= 370) // If the user pressed play again
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = START;
                            }
                            break;
                    }
                }
                break;
        }
    }
}