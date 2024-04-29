#include "headers/GameLogic.h"

int main( int argc, char *argv[])
{
    InitSDL();

    CreateApple(&apple), CreateSnake(&snake), CreateStars(stars);

    while(!quit && snake.state)
    {
        HandleInput(&snake);
        Render(renderer);
    }

    QuitSDL();
    return 0;
}