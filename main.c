#include "headers/GameLogic.h"

int main( int argc, char *argv[])
{
    InitSDL();

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
                CreateApple(&apple), CreateSnake(&snake), CreateStars(stars);
                while(!quit && snake.state)
                {
                    HandleGameInput(&snake);
                    RenderGame(renderer);
                }
                break;

            // Exit the game
            case EXIT:
                quit = true;
                break;

            // Show the mode
            /*
                !: This case is still not implemented
                case MODE:
                    break;
            */

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