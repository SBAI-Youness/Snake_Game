#include "headers/GameLogic.h"

GameMode currentMode;

int main( int argc, char *argv[])
{
    InitSDL();
    InitializeHighestScore(&snake);

    while(!quit)
    {
        switch(MenuOption)
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
                    currentMode = MODE_SINGLE_PLAYER;
                    isHovering = onMode1;
                    CreateApple(&apple), CreateSnake( &snake, 40, 0), CreateStars(stars);
                    while(!quit && snake.state)
                    {
                        HandleMode1Input(&snake);
                        RenderMode1(renderer);
                    }
                }
                else if(isHovering == onMode2 || currentMode == MODE_TWO_PLAYERS)
                {
                    currentMode = MODE_TWO_PLAYERS;
                    isHovering = onMode2;
                    CreateApple(&apple), CreateSnake( &snake1, 40, 0), CreateSnake( &snake2, 40, 480), CreateStars(stars);
                    while(!quit) // TODO: This game loop should also depend on the time (1 minute)
                    {
                        HandleMode2Input( &snake1, &snake2);
                        RenderMode2(renderer);
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

    QuitSDL();
    return 0;
}