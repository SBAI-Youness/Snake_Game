#include "headers/GameLogic.h"

int main( int argc, char *argv[])
{
    InitSDL();

    while(!quit)
    {
        switch(MenuOption)
        {
            // Show the menu
            case 0:
                HandleMenuInput();
                RenderMenu(renderer);
                break;

            // Start the game
            case 1:
                CreateApple(&apple), CreateSnake(&snake), CreateStars(stars);
                while(!quit && snake.state)
                {
                    HandleGameInput(&snake);
                    RenderGame(renderer);
                }
                break;

            // Exit the game
            case 2:
                quit = true;
                break;
        }
    }

    QuitSDL();
    return 0;
}