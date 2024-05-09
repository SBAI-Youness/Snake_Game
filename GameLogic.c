#include "headers/GameLogic.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *IconSurface = NULL, *AppleSurface = NULL, *ScoreSurface = NULL, *TitleSurface = NULL, *StartSurface = NULL, *ExitSurface = NULL, *CursorSurface = NULL, *PointerSurface = NULL, *GameOverSurface = NULL;
SDL_Texture *AppleTexture = NULL, *ScoreTexture = NULL, *TitleTexture = NULL, *StartTexture = NULL, *ExitTexture = NULL, *PointerTexture = NULL, *GameOverTexture = NULL;
SDL_Cursor *Cursor = NULL;
Mix_Music *EatingMusic = NULL, *ClickingMusic = NULL, *ClickingPopMusic = NULL, *GameOverMusic = NULL;
TTF_Font *ScoreFont = NULL, *MenuFont = NULL;

player snake;
fruit apple;
star stars[NUMBER_OF_STARS];

bool quit = false;

GameState MenuOption = MENU;

MouseHoveringState isHovering = onNothing;

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

    // Loading the mp3 audio file
    ClickingMusic = Mix_LoadMUS("tools/sounds/Clicking.mp3");

    // Checking if the audio was successfully loaded
    if(!ClickingMusic)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadMUS Error: %s\n", Mix_GetError());
        QuitSDL();
    }

    // Loading the mp3 audio file
    ClickingPopMusic = Mix_LoadMUS("tools/sounds/ClickingPop.mp3");

    // Checking if the audio was successfully loaded
    if(!ClickingPopMusic)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Mix_LoadMUS Error: %s\n", Mix_GetError());
        QuitSDL();
    }

    // Loading the mp3 audio file
    GameOverMusic = Mix_LoadMUS("tools/sounds/GameOver.mp3");

    // Checking if the audio was successfully loaded
    if(!GameOverMusic)
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
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Setting the window icon with IconSurface
    SDL_SetWindowIcon( window, IconSurface);

    // Creating the renderer
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Checking if the renderer was successfully created
    if(!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Loading the apple image
    AppleSurface = IMG_Load("tools/images/AppleImage.png");

    // Checking if the apple image was successfully loaded
    if(!AppleSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Creating texture from surface
    AppleTexture = SDL_CreateTextureFromSurface( renderer, AppleSurface);

    // Checking if the texture was successfully created from surface
    if(!AppleTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(AppleSurface);

    // Loading the cursor image
    CursorSurface = IMG_Load("tools/images/cursor.png");

    // Checking if the cursor image was successfully loaded
    if(!CursorSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Create a color cursor from the loaded surface
    Cursor = SDL_CreateColorCursor( CursorSurface, 0, 0);

    // Checking if the cursor was successfully created
    if(!Cursor)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateColorCursor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Setting the created cursor as the active cursor for the application
    SDL_SetCursor(Cursor);

    // Loading the button's pointer image
    PointerSurface = IMG_Load("tools/images/pointer.png");

    // Checking if the button's pointer image was successfully loaded
    if(!PointerSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Creating texture from surface
    PointerTexture = SDL_CreateTextureFromSurface( renderer, PointerSurface);

    // Checking if the texture was successfully created from surface
    if(!PointerTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(PointerSurface);

    // Loading the game over image
    GameOverSurface = IMG_Load("tools/images/GameOver.png");

    // Checking if the game over image was successfully loaded
    if(!GameOverSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Creating texture from surface
    GameOverTexture = SDL_CreateTextureFromSurface( renderer, GameOverSurface);

    // Checking if the texture was successfully created from surface
    if(!GameOverTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(GameOverSurface);

    // Initialization of the SDL_ttf library
    if (TTF_Init() == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Opening a font
    ScoreFont = TTF_OpenFont("tools/fonts/MinecraftRegularFont.TTF", 28);

    // Checking if the font was successfully openned
    if(!ScoreFont)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_OpenFont Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Opening a font
    MenuFont = TTF_OpenFont("tools/fonts/TalkComic.TTF", 50);

    // Checking if the font was successfully openned
    if(!MenuFont)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_OpenFont Error: %s\n", TTF_GetError());
        QuitSDL();
    }
}

void CreateStars(star stars[])
{
    // Loop through each star
    for( int i = 0; i < NUMBER_OF_STARS; i++)
    {
        // Generation of a random position of the star within the window
        stars[i].position.x = rand() % WINDOW_WIDTH;
        stars[i].position.y = rand() % WINDOW_HEIGHT;

        // Set the velocity (speed) of the star to a random value between 1 and 6
        stars[i].velocity = ((float)rand() / RAND_MAX) * 5 + 1;

        // Set the depth of the star to a random value between 0 and 1000
        stars[i].depth = ((float)rand() / RAND_MAX) * 1000;
    }
}

void UpdateAndDrawStars( SDL_Renderer *renderer, star stars[])
{
    // Loop through each star
    for( int i = 0; i < NUMBER_OF_STARS; i++)
    {
        // Update the x-coordinate of the star based on its velocity
        stars[i].position.x -= (int)stars[i].velocity;

        // Wrap around stars that go off screen on the left side
        if(stars[i].position.x < 0)
        {
            // Reset the x-coordinate to the right edge of the window
            stars[i].position.x = WINDOW_WIDTH;

            // Randomly set the y-coordinate within the window height
            stars[i].position.y = rand() % WINDOW_HEIGHT;

            // Randomize the velocity for a new movement pattern
            stars[i].velocity = ((float)rand() / RAND_MAX) * 5 + 1;
        }

        // Calculate the size of the star based on its depth
        int size = 1 + (int)(stars[i].depth / 100);

        // Calculate the alpha value (transparency) based on the depth
        int alpha = (int)(255 - stars[i].depth / 10);

        // Set the render draw color to the calculated alpha for a fading effect
        SDL_SetRenderDrawColor(renderer, alpha, alpha, alpha, 255);
        
        // Render a single point (pixel) representing the star on the screen
        SDL_RenderDrawPoint(renderer, stars[i].position.x, stars[i].position.y);
    }

    // Introduce a small delay to control the frame rate of the animation
    SDL_Delay(10);
}

void CreateApple(fruit *apple)
{
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generation of a random position of the apple within the window
    apple->position.x = (rand() % (WINDOW_WIDTH / SNAKE_SIZE)) * SNAKE_SIZE;
    apple->position.y = (rand() % (WINDOW_HEIGHT / SNAKE_SIZE)) * SNAKE_SIZE;
}

void DrawApple(SDL_Renderer *renderer)
{
    // Rendering an image that is representing the apple
    SDL_Rect AppleCell = { apple.position.x, apple.position.y, SNAKE_SIZE, SNAKE_SIZE};
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

void DrawSnake(SDL_Renderer *renderer)
{
    // Setting the snake's color to green
    if(SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_SetRenderDrawColor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Drawing rectangles that are representing each chunk of the snake
    for( int i = 0; i < snake.size; i++)
    {
        SDL_Rect SnakeSegment = { snake.chunk[i].position.x, snake.chunk[i].position.y, SNAKE_SIZE, SNAKE_SIZE};
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

    // Check if the snake's head collides with its body
    for( int i = 1; i < snake->size; i++)
    {
        if(snake->chunk[0].position.x == snake->chunk[i].position.x && snake->chunk[0].position.y == snake->chunk[i].position.y && snake->score != 0)
        {
            snake->state = false; // Snake collides with itself, game over
            MenuOption = GAMEOVER;
            Mix_PlayMusic( GameOverMusic, 0);
            break;
        }
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
        snake->size++, snake->score++, snake->speed = (snake->speed > 50)? snake->speed -= 2: snake->speed;
        CreateApple(&apple);
    }

    // Checking if the apple is generated on the body of the snake
    for( int i = 0; i < snake->size; i++)
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

void HandleGameInput(player *snake)
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
                    case SDLK_z:
                    case SDLK_UP:
                        snake->chunk[0].direction = UP;
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        snake->chunk[0].direction = RIGHT;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        snake->chunk[0].direction = DOWN;
                        break;
                    case SDLK_q:
                    case SDLK_LEFT:
                        snake->chunk[0].direction = LEFT;
                        break;
                }
                break;
        }
    }
}

void RenderMenu(SDL_Renderer *renderer)
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

    // Setting colors for the game title and the buttons
    SDL_Color TitleColor = { 255, 255, 255, 255}, DefaultColor = { 128, 128, 128, 128}, HoveringColor = { 160, 160, 160, 255};

    // Render the texts onto surfaces using the provided fonts and colors
    TitleSurface = TTF_RenderText_Solid( MenuFont, "Snake Game", TitleColor);
    StartSurface = TTF_RenderText_Solid( MenuFont, "Start", (isHovering != onStart)? DefaultColor: HoveringColor);
    ExitSurface = TTF_RenderText_Solid( MenuFont, "Exit", (isHovering != onExit)? DefaultColor: HoveringColor);

    // Checking if the texts were successfully rendered
    if(!TitleSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }
    if(!StartSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }
    if(!ExitSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create textures from the rendered surfaces
    TitleTexture = SDL_CreateTextureFromSurface( renderer, TitleSurface);
    StartTexture = SDL_CreateTextureFromSurface( renderer, StartSurface);
    ExitTexture = SDL_CreateTextureFromSurface( renderer, ExitSurface);

    // Checking if the textures were successfully created
    if(!TitleTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }
    if(!StartTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }
    if(!ExitTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Creating rectangles where the textures will be copied
    SDL_Rect TitleRect = { 125, 20, 550, 120}, StartRect = { 250, 210, 300, 80}, ExitRect = { 250, 300, 300, 80};

    // Rendering the textures onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, TitleTexture, NULL, &TitleRect);
    SDL_RenderCopy( renderer, StartTexture, NULL, &StartRect);
    SDL_RenderCopy( renderer, ExitTexture, NULL, &ExitRect);

    switch(isHovering)
    {
        case onStart:
            SDL_RenderCopy( renderer, PointerTexture, NULL, &(SDL_Rect){ 200, 230, 40, 40});
            break;

        case onExit:
            SDL_RenderCopy( renderer, PointerTexture, NULL, &(SDL_Rect){ 200, 320, 40, 40});
            break;
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
}

void RenderGameOver(SDL_Renderer *renderer)
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

    SDL_RenderCopy( renderer, GameOverTexture, NULL, &(SDL_Rect){ 200, 40, 400, 170});

    SDL_RenderPresent(renderer);
}

void HandleGameOverInput()
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
        }
    }
}

void HandleMenuInput()  
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
                        if (isHovering != onStart)
                        {
                            isHovering = onStart;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                        break;
                    case SDLK_DOWN:
                        if (isHovering != onExit)
                        {
                            isHovering = onExit;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                        break;
                    case SDLK_RETURN:
                        Mix_HaltMusic();
                        Mix_PlayMusic( ClickingMusic, 0);
                        MenuOption = isHovering;
                        break;
                }
                break;

            // This case case is related to mouse motions
            case SDL_MOUSEMOTION:
                // Extract the x and y coordinates of the mouse pointer from the event
                int mouseX = event.motion.x, mouseY = event.motion.y;

                if(mouseX >= 250 && mouseX <= 550 && mouseY >= 210 && mouseY <= 290) // Mouse is hovering start button
                {
                    if(isHovering != onStart)
                    {
                        isHovering = onStart;
                        Mix_PlayMusic( ClickingPopMusic, 0);
                    }
                }
                else if(mouseX >= 250 && mouseX <= 550 && mouseY >= 300 && mouseY <= 380) // Mouse is hovering exit button
                {
                    if (isHovering != onExit)
                    {
                        isHovering = onExit;
                        Mix_PlayMusic( ClickingPopMusic, 0);
                    }
                }
                else // Mouse is hovering any button
                    isHovering = onNothing;
                break;

            // If a mouse button is released
            case SDL_MOUSEBUTTONUP:
                // Handle mouse input
                switch(event.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        int mouseX = event.button.x, mouseY = event.button.y;

                        if(mouseX >= 250 && mouseX <= 550 && mouseY >= 210 && mouseY <= 290) // If the user pressed start
                        {
                            Mix_HaltMusic();
                            Mix_PlayMusic( ClickingMusic, 0);
                            MenuOption = START;
                        }
                        else if(mouseX >= 250 && mouseX <= 550 && mouseY >= 300 && mouseY <= 380) // If the user pressed exit
                        {
                            Mix_HaltMusic();
                            Mix_PlayMusic( ClickingMusic, 0);
                            MenuOption = EXIT;
                        }
                        break;
                }
                break;
        }
    }
}

void DrawScore( SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font)
{
    // Defining an array characters to store the score as a string
    char ScoreString[50];

    // Convert the integer score to a string using sprintf
    itoa(snake.score, ScoreString, 10);

    // Render the score string onto a surface using the provided font and color
    surface = TTF_RenderText_Solid( font, ScoreString, (SDL_Color){ 255, 255, 255, 255});

    // Checking if the text was successfully rendered
    if(!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create a texture from the rendered surface
    texture = SDL_CreateTextureFromSurface( renderer, surface);

    // Checking if the texture was successfully created
    if(!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(surface);

    // Rendering the texture onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, texture, NULL, &(SDL_Rect){ 750, 0, 40, 40});
}

void RenderGame(SDL_Renderer *renderer)
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

    UpdateAndDrawStars( renderer, stars);
    DrawApple(renderer);
    MoveSnake(&snake);
    DrawSnake(renderer);
    DrawScore( renderer, ScoreSurface, ScoreTexture, ScoreFont);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay(snake.speed);
}

void QuitSDL()
{
    if(GameOverSurface)
        SDL_FreeSurface(GameOverSurface);
    if(GameOverTexture)
        SDL_DestroyTexture(GameOverTexture);

    if(TitleSurface)
        SDL_FreeSurface(TitleSurface);
    if(StartSurface)
        SDL_FreeSurface(StartSurface);
    if(ExitSurface)
        SDL_FreeSurface(ExitSurface);
    if(TitleTexture)
        SDL_DestroyTexture(TitleTexture);
    if(StartTexture)
        SDL_DestroyTexture(StartTexture);
    if(ExitTexture)
        SDL_DestroyTexture(ExitTexture);

    if(ScoreTexture)
        SDL_DestroyTexture(ScoreTexture);
    if(ScoreFont)
        TTF_CloseFont(ScoreFont);
    TTF_Quit();
    if(Cursor)
        SDL_FreeCursor(Cursor);
    if(CursorSurface)
        SDL_FreeSurface(CursorSurface);
    if(AppleTexture)
        SDL_DestroyTexture(AppleTexture);
    if(renderer)
        SDL_DestroyRenderer(renderer);
    if(window)
        SDL_DestroyWindow(window);
    if(IconSurface)
        SDL_FreeSurface(IconSurface);
    IMG_Quit();
    if(GameOverMusic)
        Mix_FreeMusic(GameOverMusic);
    if(ClickingPopMusic)
        Mix_FreeMusic(ClickingPopMusic);
    if(ClickingMusic)
        Mix_FreeMusic(ClickingMusic);
    if(EatingMusic)
        Mix_FreeMusic(EatingMusic);
    Mix_CloseAudio();
    SDL_Quit();
}