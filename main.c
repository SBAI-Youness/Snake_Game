#include "headers/GameLogic.h"

GameMode currentMode; int countDown; Uint32 startTime;

int main( int argc, char *argv[])
{
    InitSDL(); // Initialize SDL
    InitializeHighestScore(&snake); // Initialize the highest score

    while(!quit) // Game loop
    {
        switch(MenuOption) // Switch statement to handle the menu options
        {
            // Show the menu
            case MENU:
                HandleMenuInput();
                RenderMenu(renderer);
                break;

            // Start the game
            case START:
                if(isHovering == onMode1 || currentMode == MODE_SINGLE_PLAYER)
                {
                    currentMode = MODE_SINGLE_PLAYER; isHovering = onMode1;
                    CreateApple(&apple), CreateSnake( &snake, 40, 0), CreateStars(stars);
                    while(!quit && snake.state) // Game loop for single player mode
                    {
                        HandleMode1Input(&snake);
                        RenderMode1(renderer);
                    }
                }
                else if(isHovering == onMode2 || currentMode == MODE_TWO_PLAYERS)
                {
                    currentMode = MODE_TWO_PLAYERS; isHovering = onMode2;
                    startTime = SDL_GetTicks(); countDown = 60; // 1 minute countdown
                    CreateApple(&apple), CreateSnake( &snake1, 40, 0), CreateSnake( &snake2, 40, 480), CreateStars(stars);
                    while(!quit) // Game loop for two players mode
                    {
                        HandleMode2Input( &snake1, &snake2);
                        RenderMode2( renderer, &countDown, &startTime);
                    }
                }
                break;

            // Exit the game
            case EXIT:
                quit = true;
                break;

            // Show the modes
            case MODE:
                currentMode = NONE;
                HandleModeInput();
                RenderMode(renderer);
                break;

            // Show the game over
            case GAMEOVER:
                HandleGameOverInput();
                RenderGameOver(renderer);
                break;
        }
    }

    QuitSDL(); // Quit SDL
    return 0;
}