#include "headers/declarations.h"

int main( int argc, char *argv[])
{
    InitSDL();

    CreateApple(&apple);
    CreateSnake(&snake);

    while(!quit && snake.state)
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
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Initialization of the SDL audio system with specified parameters
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_OpenAudio Error: %s\n", Mix_GetError());
        QuitSDL();
    }

    // Loading the mp3 audio file
    EatingMusic = Mix_LoadMUS("tools/sounds/SnakeEats.mp3");

    // Checking if the audio was successfully loaded
    if(!EatingMusic)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadMUS Error: %s\n", Mix_GetError());
        QuitSDL();
    }

    // Initialization of the PNG images
    if(!IMG_Init(IMG_INIT_PNG))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Loading the window icon image
    IconSurface = IMG_Load("tools/images/WindowIcon.png");

    // Checking if the image was successfully loaded
    if(!IconSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Creating the window
    window = SDL_CreateWindow( "Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    // Checking if the window was successfully created
    if(!window)
    {
        SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Setting the window icon with IconSurface
    SDL_SetWindowIcon( window, IconSurface);

    // Creating the renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Checking if the renderer was successfully created
    if(!renderer)
    {
        SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Loading the apple image
    AppleSurface = IMG_Load("tools/images/AppleImage.png");

    // Checking if the apple image was successfully loaded
    if(!AppleSurface)
    {
        SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Creating texture from surface
    AppleTexture = SDL_CreateTextureFromSurface( renderer, AppleSurface);

    // Checking if the texture was successfully created from surface
    if(!AppleTexture)
    {
        SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(AppleSurface);
}

void CreateApple(fruit *apple)
{
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generation of a random position of the apple within the window
    apple->position.x = (rand() % (WINDOW_WIDTH / SNAKE_SIZE)) * SNAKE_SIZE;
    apple->position.y = (rand() % (WINDOW_HEIGHT / SNAKE_SIZE)) * SNAKE_SIZE;
}

void DrawApple( SDL_Renderer *renderer, fruit *apple)
{
    // Setting the apple's color to red
    if(SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Drawing a rectangle that is representing the apple
    SDL_Rect AppleCell = { apple->position.x, apple->position.y, SNAKE_SIZE, SNAKE_SIZE};
    SDL_RenderCopy( renderer, AppleTexture, NULL, &AppleCell);
}

void CreateSnake(player *snake)
{
    // Setting the snake to its initial parameters
    snake->size = SNAKE_INITIAL_SIZE, snake->score = 0, snake->state = true, snake->speed = 100;

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
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Drawing rectangles that are representing each chunk of the snake
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

    // Generating another position of the apple, increasing the size of the snake and playing a sound if the apple has been eaten by the snake 
    if(snake->chunk[0].position.x == apple.position.x && snake->chunk[0].position.y == apple.position.y)
    {
        Mix_PlayMusic( EatingMusic, 0);
        snake->size++, snake->score++, snake->speed = (snake->speed > 50)? snake->speed -= .2: snake->speed;
        CreateApple(&apple);
    }

    // Checking if the apple is generated on the body of the snake
    for( int i = 1; i < snake->size; i++)
    {
        if(snake->chunk[i].position.x == apple.position.x && snake->chunk[i].position.y == apple.position.y)
        {
            CreateApple(&apple);
            break;
        }
    }

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
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Clearing the rendering target
    if(SDL_RenderClear(renderer))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    DrawApple( renderer, &apple);
    MoveSnake(&snake);
    DrawSnake( renderer, &snake);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay(snake.speed);
}

void QuitSDL()
{
    if(AppleTexture)
        SDL_DestroyTexture(AppleTexture);
    if(renderer)
        SDL_DestroyRenderer(renderer);
    if(window)
        SDL_DestroyWindow(window);
    if(IconSurface)
        SDL_FreeSurface(IconSurface);
    IMG_Quit();
    if(EatingMusic)
        Mix_FreeMusic(EatingMusic);
    Mix_CloseAudio();
    SDL_Quit();
}