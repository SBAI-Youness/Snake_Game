#include "../headers/sdl_utils.h"
#include "../headers/game_logic.h"
#include "../headers/input.h"
#include "../headers/render.h"

int countDown;
Uint32 startTime;
GameMode currentMode;

int main( int argc, char *argv[])
{
    InitSDL(); // Initialize SDL
    InitializeHighestScore(&snake); // Initialize the highest score

    while (!quit) // Game loop
    {
        switch (MenuOption) // Switch statement to handle the menu options
        {
            case MENU: // Render the menu
                HandleMenuInput();
                RenderMenu(renderer);
                break;

            case START: // Start the game
                if (isHovering == onMode1 || currentMode == MODE_SINGLE_PLAYER) // Single player mode
                {
                    isHovering = onMode1;
                    currentMode = MODE_SINGLE_PLAYER;

                    CreateApple(&apple);
                    CreateSnake( &snake, 40, 0);
                    CreateStars(stars);
                    while (!quit && snake.state) // Game loop for single player mode
                    {
                        HandleMode1Input(&snake);
                        RenderMode1(renderer);
                    }
                }
                else if (isHovering == onMode2 || currentMode == MODE_TWO_PLAYERS) // Two players mode
                {
                    isHovering = onMode2;
                    currentMode = MODE_TWO_PLAYERS;
                    
                    startTime = SDL_GetTicks(); // Start the timer
                    countDown = 60; // 1 minute countdown
                    CreateApple(&apple);
                    CreateSnake( &snake1, 40, 0); CreateSnake( &snake2, 40, 480);
                    CreateStars(stars);
                    while (!quit && countDown) // Game loop for two players mode
                    {
                        HandleMode2Input( &snake1, &snake2);
                        RenderMode2( renderer, &countDown, &startTime);
                    }
                }
                break;

            case EXIT: // Exit the game
                quit = true;
                break;

            case MODE: // Mode selection screen
                currentMode = NONE;
                HandleModeInput();
                RenderMode(renderer);
                break;

            case GAMEOVER1: // Game over screen for single player mode
                HandleGameOverMode1Input();
                RenderGameOverMode1(renderer);
                break;

            case GAMEOVER2: // Game over screen for two players mode
                HandleGameOverMode2Input();
                RenderGameOverMode2(renderer);
                break;
        }
    }

    QuitSDL(); // Quit SDL
    return 0;
}