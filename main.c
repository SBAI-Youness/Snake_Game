#include "headers/declarations.h"

int main( int argc, char *argv[])
{
    InitSDL();

    CreateSnake(&snake);

    while(!quit)
    {
        HandleInput(&snake);
        Render(renderer);
    }

    QuitSDL();
    return 0;
}

void InitSDL()
{
    // Initialization of the SDL2 library
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        fprintf( stderr, "SDL_Init Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Initialization of the PNG images
    if(!IMG_Init(IMG_INIT_PNG))
    {
        fprintf( stderr, "IMG_Init Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Loading the window icon image
    IconSurface = IMG_Load("tools/images/WindowIcon.png");

    // Checking if the image was successfully loaded
    if(!IconSurface)
    {
        fprintf( stderr, "IMG_Load Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Creating the window
    window = SDL_CreateWindow( "Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // Checking if the window was successfully created
    if(!window)
    {
        fprintf( stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Setting the window icon with IconSurface
    SDL_SetWindowIcon( window, IconSurface);

    // Creating the renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Checking if the renderer was successfully created
    if(!renderer)
    {
        fprintf( stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        QuitSDL();
    }
}

void DrawGrid(SDL_Renderer *renderer)
{
    // Setting the grid's color to grey
    if(SDL_SetRenderDrawColor( renderer, 128, 128, 128, 255))
    {
        fprintf( stderr, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    for( int i = 0; i < GRID_ROWS_SIZE; i++)
    {
        for( int j = 0; j < GRID_COLUMNS_SIZE; j++)
        {
            // Definition of a rect representing a cell in the grid
            SDL_Rect cell = { j * SNAKE_SIZE, i * SNAKE_SIZE, SNAKE_SIZE, SNAKE_SIZE};
            SDL_RenderDrawRect( renderer, &cell);
        }
    }
}

void CreateSnake(player *snake)
{
    // Setting the snake to its initial size
    snake->size = SNAKE_INITIAL_SIZE;

    // Setting each chunk to its position
    for( int i = 0; i < snake->size; i++)
    {
        snake->chunk[i].position.x = - i * SNAKE_SIZE;
        snake->chunk[i].position.y = 0;
    }
}

void DrawSnake( SDL_Renderer *renderer, player *snake)
{
    // Setting the snake's color to green
    if(SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255))
    {
        fprintf( stderr, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Drawing rects that are representing each chunk of the snake
    for( int i = 0; i < snake->size; i++)
    {
        SDL_Rect SnakeSegment = { snake->chunk[i].position.x, snake->chunk[i].position.y, SNAKE_SIZE, SNAKE_SIZE};
        SDL_RenderDrawRect( renderer, &SnakeSegment);
        SDL_RenderFillRect( renderer, &SnakeSegment);
    }
}

void MoveSnake(player *snake)
{
    // Switch statement to handle snake movement based on its direction
    switch(snake->chunk[0].direction)
    {
        case UP:
            snake->chunk[0].position.y -= SNAKE_SIZE;
            break;
        case RIGHT:
            snake->chunk[0].position.x += SNAKE_SIZE;
            break;
        case DOWN:
            snake->chunk[0].position.y += SNAKE_SIZE;
            break;
        case LEFT:
            snake->chunk[0].position.x -= SNAKE_SIZE;
            break;
    }

    // Adjust snake position if it moves beyond the window boundaries
    if(snake->chunk[0].position.y < 0)
        snake->chunk[0].position.y = WINDOW_HEIGHT - SNAKE_SIZE;
    else if (snake->chunk[0].position.x < 0)
        snake->chunk[0].position.x = WINDOW_WIDTH - SNAKE_SIZE;
    else if(snake->chunk[0].position.y >= WINDOW_HEIGHT)
        snake->chunk[0].position.y = 0;
    else if (snake->chunk[0].position.x >= WINDOW_WIDTH)
        snake->chunk[0].position.x = 0;

    // Shift the positions of snake chunks to follow the head
    for( int i = snake->size-1; i > 0; i--)
        snake->chunk[i] = snake->chunk[i-1]; // Assign the position of the previous chunk to the current chunk
}

void HandleInput(player *snake)
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
                // Handle keyboard input
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:
                        snake->chunk[0].direction = UP;
                        break;
                    case SDLK_RIGHT:
                        snake->chunk[0].direction = RIGHT;
                        break;
                    case SDLK_DOWN:
                        snake->chunk[0].direction = DOWN;
                        break;
                    case SDLK_LEFT:
                        snake->chunk[0].direction = LEFT;
                        break;
                }
                break;
        }
    }
}

void Render(SDL_Renderer *renderer)
{
    // Set the window color to black
    if(SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255))
    {
        fprintf( stderr, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Clearing the rendering target
    if(SDL_RenderClear(renderer))
    {
        fprintf( stderr, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    DrawGrid(renderer);
    MoveSnake(&snake);
    DrawSnake( renderer, &snake);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay(100);
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