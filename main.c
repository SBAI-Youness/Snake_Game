#include "headers/dec.h"

int main( int argc, char *argv[])
{
    InitSDL();

    while(!quit)
    {
        HandleInput();
        Render(renderer);
    }
    QuitSDL();
    return 0;
}

void InitSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        fprintf( stderr, "SDL_Init Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        fprintf( stderr, "IMG_Init Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    IconSurface = IMG_Load("tools/images/WindowIcon.png");

    if(!IconSurface)
    {
        fprintf( stderr, "IMG_Load Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    window = SDL_CreateWindow( "Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    if(!window)
    {
        fprintf( stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    SDL_SetWindowIcon( window, IconSurface);

    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!renderer)
    {
        fprintf( stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        QuitSDL();
    }
}

void HandleInput()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
}

void Render(SDL_Renderer *renderer)
{
    if(SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255))
    {
        fprintf( stderr, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }
    if(SDL_RenderClear( renderer))
    {
        fprintf( stderr, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    SDL_RenderPresent( renderer);
}

void QuitSDL()
{
    if(renderer)
        SDL_DestroyRenderer(renderer);
    if(IconSurface)
        SDL_FreeSurface(IconSurface);
    IMG_Quit();
    if(window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}