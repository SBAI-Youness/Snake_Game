#include "../headers/sdl_utils.h"
#include "../headers/menu_logic.h"
#include "../headers/game_logic.h"

// Input

void HandleMenuInput()
{
    // Event handling loop
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        // Handle each event type
        switch(event.type)
        {
            // If the user quits the game
            case SDL_QUIT:
                quit = true;
                break;

            // If a key is pressed
            case SDL_KEYDOWN:
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle keyboard input
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            if(isHovering == onStart)
                                isHovering = onExit;
                            else if(isHovering == onExit)
                                isHovering = onStart;
                            else
                                isHovering = onStart;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_DOWN:
                            if(isHovering == onStart)
                                isHovering = onExit;
                            else if(isHovering == onExit)
                                isHovering = onStart;
                            else
                                isHovering = onExit;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_RETURN:
                            if(isHovering == onStart)
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MODE;
                            }
                            else if(isHovering == onExit)
                            {
                                MenuOption = EXIT;
                            }
                            break;
                    }
                }
                break;

            // This case is related to mouse motions
            case SDL_MOUSEMOTION:
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Extract the x and y coordinates of the mouse pointer from the event
                    int mouseX = event.motion.x, mouseY = event.motion.y;

                    if(mouseX >= 280 && mouseX <= 500 && mouseY >= 150 && mouseY <= 230) // Mouse is hovering start button
                    {
                        if(isHovering != onStart)
                        {
                            isHovering = onStart;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if(mouseX >= 280 && mouseX <= 500 && mouseY >= 240 && mouseY <= 320) // Mouse is hovering exit button
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
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle mouse input
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            int mouseX = event.button.x, mouseY = event.button.y;

                            if(mouseX >= 280 && mouseX <= 500 && mouseY >= 150 && mouseY <= 230) // If the user pressed start
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MODE;
                            }
                            else if(mouseX >= 280 && mouseX <= 500 && mouseY >= 240 && mouseY <= 320) // If the user pressed exit
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
    while(SDL_PollEvent(&event))
    {
        // Handle each event type
        switch(event.type)
        {
            // If the user quits the game
            case SDL_QUIT:
                quit = true;
                break;

            // If a key is pressed
            case SDL_KEYDOWN:
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle keyboard input
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            if(isHovering == onMode1)
                                isHovering = onMode2;
                            else if(isHovering == onMode2)
                                isHovering = onMode1;
                            else
                                isHovering = onMode1;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_DOWN:
                            if(isHovering == onMode1)
                                isHovering = onMode2;
                            else if(isHovering == onMode2)
                                isHovering = onMode1;
                            else
                                isHovering = onMode2;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_RETURN:
                            if(isHovering == onMode1 || isHovering == onMode2)
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
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Extract the x and y coordinates of the mouse pointer from the event
                    int mouseX = event.motion.x, mouseY = event.motion.y;

                    if(mouseX >= 10 && mouseX <= 60 && mouseY >= 10 && mouseY <= 60) // Mouse is hovering the return button
                    {
                        if(isHovering != onReturn)
                        {
                            isHovering = onReturn;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if(mouseX >= 325 && mouseX <= 475 && mouseY >= 150 && mouseY <= 220) // Mouse is hovering the first mode
                    {
                        if(isHovering != onMode1)
                        {
                            isHovering = onMode1;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if(mouseX >= 325 && mouseX <= 475 && mouseY >= 240 && mouseY <= 310) // Mouse is hovering the second mode
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
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle mouse input
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            int mouseX = event.button.x, mouseY = event.button.y;

                            if(mouseX >= 10 && mouseX <= 60 && mouseY >= 10 && mouseY <= 60) // Mouse is hovering the return button
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MENU;
                            }
                            else if(mouseX >= 325 && mouseX <= 475 && mouseY >= 150 && mouseY <= 220) // If the user pressed the first mode
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = START;
                            }
                            else if(mouseX >= 325 && mouseX <= 475 && mouseY >= 240 && mouseY <= 310) // If the user pressed the second mode
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
    while(SDL_PollEvent(&event))
    {
        // Handle each event type
        switch(event.type)
        {
            // If the user quits the game
            case SDL_QUIT:
                quit = true;
                break;

            // If a key is pressed
            case SDL_KEYDOWN:
                if(directionChanged) break;

                // Handle keyboard input
                switch(event.key.keysym.sym)
                {
                    case SDLK_z:
                    case SDLK_UP:
                        if(snake->chunk[0].direction != DOWN)
                        {
                            snake->chunk[0].direction = UP;
                            snake->chunk[0].angle = -90;
                            directionChanged = true;
                        }
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        if(snake->chunk[0].direction != LEFT)
                        {
                            snake->chunk[0].direction = RIGHT;
                            snake->chunk[0].angle = 0;
                            directionChanged = true;
                        }
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        if(snake->chunk[0].direction != UP)
                        {
                            snake->chunk[0].direction = DOWN;
                            snake->chunk[0].angle = 90;
                            directionChanged = true;
                        }
                        break;
                    case SDLK_q:
                    case SDLK_LEFT:
                        if(snake->chunk[0].direction != RIGHT)
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
    while(SDL_PollEvent(&event))
    {
        // Handle each event type
        switch(event.type)
        {
            // If the user quits the game
            case SDL_QUIT:
                quit = true;
                break;

            // If a key is pressed
            case SDL_KEYDOWN:
                // Handle keyboard input
                switch(event.key.keysym.sym)
                {
                    // Input handling for the player number 1
                    case SDLK_UP:
                        if(!direction1Changed && snake1->chunk[0].direction != DOWN)
                        {
                            snake1->chunk[0].direction = UP;
                            snake1->chunk[0].angle = -90;
                            direction1Changed = true;
                        }
                        break;
                    case SDLK_RIGHT:
                        if(!direction1Changed && snake1->chunk[0].direction != LEFT)
                        {
                            snake1->chunk[0].direction = RIGHT;
                            snake1->chunk[0].angle = 0;
                            direction1Changed = true;
                        }
                        break;
                    case SDLK_DOWN:
                        if(!direction1Changed && snake1->chunk[0].direction != UP)
                        {
                            snake1->chunk[0].direction = DOWN;
                            snake1->chunk[0].angle = 90;
                            direction1Changed = true;
                        }
                        break;
                    case SDLK_LEFT:
                        if(!direction1Changed && snake1->chunk[0].direction != RIGHT)
                        {
                            snake1->chunk[0].direction = LEFT;
                            snake1->chunk[0].angle = 180;
                            direction1Changed = true;
                        }
                        break;

                    // Input handling for the player number 2
                    case SDLK_z:
                        if(!direction2Changed && snake2->chunk[0].direction != DOWN)
                        {
                            snake2->chunk[0].direction = UP;
                            snake2->chunk[0].angle = -90;
                            direction2Changed = true;
                        }
                        break;
                    case SDLK_d:
                        if(!direction2Changed && snake2->chunk[0].direction != LEFT)
                        {
                            snake2->chunk[0].direction = RIGHT;
                            snake2->chunk[0].angle = 0;
                            direction2Changed = true;
                        }
                        break;
                    case SDLK_s:
                        if(!direction2Changed && snake2->chunk[0].direction != UP)
                        {
                            snake2->chunk[0].direction = DOWN;
                            snake2->chunk[0].angle = 90;
                            direction2Changed = true;
                        }
                        break;
                    case SDLK_q:
                        if(!direction2Changed && snake2->chunk[0].direction != RIGHT)
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

void HandleGameOverInput()
{
    // Event handling loop
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        // Handle each event type
        switch(event.type)
        {
            // If the user quits the game
            case SDL_QUIT:
                quit = true;
                break;

            // If a key is pressed
            case SDL_KEYDOWN:
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle keyboard input
                    switch(event.key.keysym.sym)
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
                            if(isHovering == onHome || isHovering == onPlayAgain)
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
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Extract the x and y coordinates of the mouse pointer from the event
                    int mouseX = event.motion.x, mouseY = event.motion.y;

                    if(mouseX >= 290 && mouseX <= 360 && mouseY >= 300 && mouseY <= 370) // Mouse is hovering home button
                    {
                        if(isHovering != onHome)
                        {
                            isHovering = onHome;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if(mouseX >= 440 && mouseX <= 510 && mouseY >= 300 && mouseY <= 370) // Mouse is hovering play again button
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
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle mouse input
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            int mouseX = event.button.x, mouseY = event.button.y;

                            if(mouseX >= 290 && mouseX <= 360 && mouseY >= 300 && mouseY <= 370) // If the user pressed home
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MENU;
                            }
                            else if(mouseX >= 440 && mouseX <= 510 && mouseY >= 300 && mouseY <= 370) // If the user pressed play again
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

// Render

void RenderMenuBackgroundImage(SDL_Renderer *renderer)
{
    // Load the image file into a surface
    SDL_Surface *surface = IMG_Load("../tools/images/MenuBackground.png");

    // Checking if the surface was successfully loaded
    if(!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Create a texture from the surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, surface);

    // Checking if the texture was successfully created
    if(!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Freeing the surface after creating the texture
    SDL_FreeSurface(surface);

    // Render the texture onto the renderer
    SDL_RenderCopy( renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}

void RenderCreator( SDL_Renderer *renderer, char Creator[])
{
    // Defining a string to store the text "Created by: Creator"
    char CreatorString[100];

    // Copy the text "Created by: Creator" to the string CreatorString using the sprintf function
    sprintf(CreatorString, "Created by: %s", Creator);

    // Render the text "Created by: Youness SBAI" using the provided font and color
    SDL_Surface *CreatedBySurface = TTF_RenderText_Solid( font32, CreatorString, (SDL_Color){ 179, 59, 0, 255});

    // Checking if the surface was successfully created
    if(!CreatedBySurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create a texture from the surface
    SDL_Texture *CreatedByTexture = SDL_CreateTextureFromSurface( renderer, CreatedBySurface);

    // Checking if the texture was successfully created
    if(!CreatedByTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(CreatedBySurface);

    // Render the texture onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, CreatedByTexture, NULL, &(SDL_Rect){ 20, 420, 400, 80});

    // Destroy the texture
    SDL_DestroyTexture(CreatedByTexture);
}

void RenderMenu(SDL_Renderer *renderer)
{
    // Set the window color to black
    if(SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Clearing the rendering target
    if(SDL_RenderClear(renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    RenderMenuBackgroundImage(renderer);

    RenderCreator( renderer , "Youness SBAI");

    // Setting colors for the game title and the buttons
    SDL_Color DefaultColor = { 160, 160, 160, 255}, HoveringColor = { 0, 153, 76, 255};

    // Render the texts onto surfaces using the provided fonts and colors
    SDL_Surface *TitleSurface = TTF_RenderText_Solid( font50, "Snake Game", (SDL_Color){ 0, 0, 0, 255});
    SDL_Surface *StartSurface = TTF_RenderText_Solid( font50, "Start", (isHovering != onStart)? DefaultColor: HoveringColor);
    SDL_Surface *ExitSurface = TTF_RenderText_Solid( font50, "Exit", (isHovering != onExit)? DefaultColor: HoveringColor);

    // Checking if the texts were successfully rendered
    if(!TitleSurface || !StartSurface || !ExitSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create textures from the rendered surfaces
    SDL_Texture *TitleTexture = SDL_CreateTextureFromSurface( renderer, TitleSurface);
    SDL_Texture *StartTexture = SDL_CreateTextureFromSurface( renderer, StartSurface);
    SDL_Texture *ExitTexture = SDL_CreateTextureFromSurface( renderer, ExitSurface);

    // Checking if the textures were successfully created
    if(!TitleTexture || !StartTexture || !ExitTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surfaces after they are no longer needed
    SDL_FreeSurface(TitleSurface);
    SDL_FreeSurface(StartSurface);
    SDL_FreeSurface(ExitSurface);

    // Rendering the textures onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, TitleTexture, NULL, &(SDL_Rect){ 100, 20, 600, 100});
    SDL_RenderCopy( renderer, StartTexture, NULL, &(SDL_Rect){ 280, 150, 220, 80});
    SDL_RenderCopy( renderer, ExitTexture, NULL, &(SDL_Rect){ 280, 240, 220, 80});

    switch(isHovering)
    {
        case onStart:
            SDL_RenderCopy( renderer, PointerTexture, NULL, &(SDL_Rect){ 220, 170, 50, 40});
            break;

        case onExit:
            SDL_RenderCopy( renderer, PointerTexture, NULL, &(SDL_Rect){ 220, 260, 50, 40});
    }

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Destroy the textures used in the menu
    SDL_DestroyTexture(TitleTexture);
    SDL_DestroyTexture(StartTexture);
    SDL_DestroyTexture(ExitTexture);
}

void RenderMode(SDL_Renderer *renderer)
{
    // Set the window color to black
    if(SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Clearing the rendering target
    if(SDL_RenderClear(renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    RenderMenuBackgroundImage(renderer);

    RenderCreator( renderer , "Youness SBAI");

    // Loading an image from the file
    SDL_Surface *returnSurface = IMG_Load("../tools/images/return.png");

    // Checking if the image was successfully loaded
    if(!returnSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Creating a texture from the surface
    SDL_Texture *returnTexture = SDL_CreateTextureFromSurface(renderer, returnSurface);

    // Checking if the texture was successfully created
    if(!returnTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Freeing the surface after creating the texture
    SDL_FreeSurface(returnSurface);

    // Setting colors for the game title and the buttons
    SDL_Color DefaultColor = { 160, 160, 160, 255};

    // Render the texts onto surfaces using the provided fonts and colors
    SDL_Surface *ModeSurface = TTF_RenderText_Solid( font50, "Choose the game mode:", (SDL_Color){ 0, 51, 102, 255});
    SDL_Surface *Mode1Surface = TTF_RenderText_Solid( font50, "1 Player", (isHovering != onMode1)? DefaultColor: (SDL_Color){ 0, 0, 255, 255});
    SDL_Surface *Mode2Surface = TTF_RenderText_Solid( font50, "1vs1", (isHovering != onMode2)? DefaultColor: (SDL_Color){ 255, 0, 0, 255});

    // Checking if the texts were successfully rendered
    if(!ModeSurface || !Mode1Surface || !Mode2Surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create textures from the rendered surfaces
    SDL_Texture *ModeTexture = SDL_CreateTextureFromSurface( renderer, ModeSurface);
    SDL_Texture *Mode1Texture = SDL_CreateTextureFromSurface( renderer, Mode1Surface);
    SDL_Texture *Mode2Texture = SDL_CreateTextureFromSurface( renderer, Mode2Surface);

    // Checking if the textures were successfully created
    if(!ModeTexture || !Mode1Texture || !Mode2Texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    SDL_FreeSurface(ModeSurface);
    SDL_FreeSurface(Mode1Surface);
    SDL_FreeSurface(Mode2Surface);

    SDL_RenderCopy( renderer, returnTexture, NULL, (isHovering != onReturn)? &(SDL_Rect){ 10, 10, 50, 50}: &(SDL_Rect){ 5, 5, 60, 60});

    // Rendering the textures onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, ModeTexture, NULL, &(SDL_Rect){ 175, 50, 450, 85});
    SDL_RenderCopy( renderer, Mode1Texture, NULL, &(SDL_Rect){ 325, 150, 150, 70});
    SDL_RenderCopy( renderer, Mode2Texture, NULL, &(SDL_Rect){ 325, 240, 150, 70});

    switch(isHovering)
    {
        case onMode1:
            SDL_RenderCopy( renderer, PointerTexture, NULL, &(SDL_Rect){ 265, 170, 50, 35});
            break;

        case onMode2:
            SDL_RenderCopy( renderer, PointerTexture, NULL, &(SDL_Rect){ 265, 260, 50, 35});
    }

    // Present the renderer
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(returnTexture);

    // Destroy the textures used in the game modes
    SDL_DestroyTexture(ModeTexture);
    SDL_DestroyTexture(Mode1Texture);
    SDL_DestroyTexture(Mode2Texture);
}

void RenderMode1(SDL_Renderer *renderer)
{
    // Set the window color to black
    if(SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Clearing the rendering target
    if(SDL_RenderClear(renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    UpdateAndDrawStars( renderer, stars);
    DrawApple(renderer);
    MoveSnake(&snake);
    DrawSnake( &snake, renderer, GREEN);
    DrawScore( &snake, renderer, (SDL_Color){ 255, 255, 255, 255}, (SDL_Rect){ 750, 0, 40, 40});

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay(snake.speed);
}

void RenderMode2( SDL_Renderer *renderer, int *countDown, int *startTime)
{
    // Set the window color to black
    if(SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Clearing the rendering target
    if(SDL_RenderClear(renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    UpdateAndDrawStars( renderer, stars);
    DrawApple(renderer);
    MoveSnake(&snake1), MoveSnake(&snake2);
    DrawSnake( &snake1, renderer, GREEN), DrawSnake( &snake2, renderer, BLUE);
    DrawScore( &snake1, renderer, (SDL_Color){ 0, 255, 0, 255}, (SDL_Rect){ 360, 0, 40, 40}), DrawScore( &snake2, renderer, (SDL_Color){ 0, 0, 255, 255}, (SDL_Rect){ 400, 0, 40, 40});

    Uint32 elapsed = (SDL_GetTicks() - *startTime) / 1000; // Get the elapsed time in seconds
    if (elapsed >= 1){ *countDown -= 1; *startTime = SDL_GetTicks();} // Update the countdown

    int minutes = *countDown / 60, seconds = *countDown % 60; // Convert the countdown to minutes and seconds

    char timeText[6]; // The text to be displayed for the countdown
    snprintf( timeText, sizeof(timeText), "%02d:%02d", minutes, seconds); // Format the text using snprintf

    if(*countDown > 0 && *countDown <= 10 && !Mix_PlayingMusic()) // Play the countdown music if the countdown is less than 10 seconds
        Mix_PlayMusic( BeepMusic, 1);
    else if (!*countDown) // If the countdown is finished, stop the music
        Mix_HaltMusic();

    // Render the countdown text
    RenderCountdown( renderer, timeText, (*countDown > 10)? (SDL_Color){ 153, 153, 255, 255}: (SDL_Color){ 153, 0, 0, 255}, (SDL_Rect){ 360, 460, 80, 40});

    // Present the renderer
    SDL_RenderPresent(renderer);

    if(!*countDown) quit = true; // If the countdown is finished, quit the game

    // Delay to control frame rate
    SDL_Delay((snake1.speed < snake2.speed)? snake1.speed: snake2.speed);
}

void RenderGameOver(SDL_Renderer *renderer)
{
    // Set the window color to black
    if(SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Clearing the rendering target
    if(SDL_RenderClear(renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Rendering the game over texture onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, GameOverTexture, NULL, &(SDL_Rect){ 150, 40, 500, 80});

    // Defining an array of characters to srore the final score as a string
    char FinalScoreString[60], HighestScoreString[60];

    // Convert the integer score to a string using sprintf
    sprintf( FinalScoreString, "Final Score: %d", snake.score);
    sprintf( HighestScoreString, "Highest Score: %d", snake.highestScore);

    // Render the game over visuals onto a surface using the provided font and color
    SDL_Surface *FinalScoreSurface = TTF_RenderText_Solid( font50, FinalScoreString, (SDL_Color){ 255, 255, 255, 255});
    SDL_Surface *HighestScoreSurface = TTF_RenderText_Solid( font50, HighestScoreString, (SDL_Color){ 255, 255, 255, 255});

    // Checking if the text was successfully rendered
    if(!FinalScoreSurface || !HighestScoreSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create a texture from the rendered surface
    SDL_Texture *FinalScoreTexture = SDL_CreateTextureFromSurface( renderer, FinalScoreSurface);
    SDL_Texture *HighestScoreTexture = SDL_CreateTextureFromSurface( renderer, HighestScoreSurface);

    // Checking if the texture was successfully created
    if(!FinalScoreTexture || !HighestScoreTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(FinalScoreSurface);
    SDL_FreeSurface(HighestScoreSurface);

    // Rendering the texture onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, FinalScoreTexture, NULL, &(SDL_Rect){ 250, 160, 300, 60});
    SDL_RenderCopy( renderer, HighestScoreTexture, NULL, &(SDL_Rect){ 540, 440, 250, 60});
    SDL_RenderCopy( renderer, HomeTexture, NULL, (isHovering != onHome)? &(SDL_Rect){ 290, 300, 70, 70}: &(SDL_Rect){ 285, 295, 80, 80});
    SDL_RenderCopy( renderer, PlayAgainTexture, NULL, (isHovering != onPlayAgain)? &(SDL_Rect){ 440, 300, 70, 70}: &(SDL_Rect){ 435, 295, 80, 80});

    // Presenting the renderer
    SDL_RenderPresent(renderer);

    // Destroy the textures used in the game over
    SDL_DestroyTexture(FinalScoreTexture);
    SDL_DestroyTexture(HighestScoreTexture);
}