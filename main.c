#include "headers\sdl_utils.h"
#include "headers\game_logic.h"
#include "headers\menu_logic.h"

GameMode currentMode; int countDown; Uint32 startTime;

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
                    currentMode = MODE_SINGLE_PLAYER; isHovering = onMode1;
                    CreateApple(&apple), CreateSnake( &snake, 40, 0), CreateStars(stars);
                    while (!quit && snake.state) // Game loop for single player mode
                    {
                        HandleMode1Input(&snake);
                        RenderMode1(renderer);
                    }
                }
                else if (isHovering == onMode2 || currentMode == MODE_TWO_PLAYERS) // Two players mode
                {
                    currentMode = MODE_TWO_PLAYERS; isHovering = onMode2;
                    startTime = SDL_GetTicks(); countDown = 60; // 1 minute countdown
                    CreateApple(&apple), CreateSnake( &snake1, 40, 0), CreateSnake( &snake2, 40, 480), CreateStars(stars);
                    while (!quit) // Game loop for two players mode
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

            case GAMEOVER: // Game over screen
                HandleGameOverInput();
                RenderGameOver(renderer);
                break;
        }
    }

    QuitSDL(); // Quit SDL
    return 0;
}