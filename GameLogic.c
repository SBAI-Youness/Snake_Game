#include "headers/GameLogic.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *IconSurface = NULL, *AppleSurface = NULL, *ScoreSurface = NULL, *CursorSurface = NULL, *PointerSurface = NULL, *GameOverSurface = NULL, *GreenSnakeHeadSurface = NULL, *GreenSnakeBodySurface = NULL, *GreenSnakeCornerSurface = NULL, *GreenSnakeTailSurface = NULL, *BlueSnakeHeadSurface = NULL, *BlueSnakeBodySurface = NULL, *BlueSnakeCornerSurface = NULL, *BlueSnakeTailSurface = NULL, *HomeSurface = NULL, *PlayAgainSurface = NULL;
SDL_Texture *AppleTexture = NULL, *ScoreTexture = NULL, *PointerTexture = NULL, *GameOverTexture = NULL, *GreenSnakeHeadTexture = NULL, *GreenSnakeBodyTexture = NULL, *GreenSnakeCornerTexture = NULL, *GreenSnakeTailTexture = NULL, *BlueSnakeHeadTexture = NULL, *BlueSnakeBodyTexture = NULL, *BlueSnakeCornerTexture = NULL, *BlueSnakeTailTexture = NULL, *HomeTexture = NULL, *PlayAgainTexture = NULL;
SDL_Cursor *Cursor = NULL;
Mix_Music *EatingMusic = NULL, *ClickingMusic = NULL, *ClickingPopMusic = NULL, *GameOverMusic = NULL;
TTF_Font *ScoreFont = NULL, *MenuFont = NULL;

player snake, snake1, snake2;
fruit apple;
star stars[NUMBER_OF_STARS];

bool quit = false;

GameState MenuOption = MENU;

MouseHoveringState isHovering = onNothing;

SnakeColor color;

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
    ClickingMusic = Mix_LoadMUS("tools/sounds/Clicking.mp3");
    ClickingPopMusic = Mix_LoadMUS("tools/sounds/ClickingPop.mp3");
    GameOverMusic = Mix_LoadMUS("tools/sounds/GameOver.mp3");

    // Checking if the audio was successfully loaded
    if(!EatingMusic || !ClickingMusic || !ClickingPopMusic || !GameOverMusic)
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
    window = SDL_CreateWindow( "Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

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

    // Loading image files
    AppleSurface = IMG_Load("tools/images/AppleImage.png");
    PointerSurface = IMG_Load("tools/images/pointer.png");
    GameOverSurface = IMG_Load("tools/images/GameOver.png");
    HomeSurface = IMG_Load("tools/images/home.png");
    PlayAgainSurface = IMG_Load("tools/images/PlayAgain.png");

    // Checking if the image was successfully loaded
    if(!AppleSurface || !PointerSurface || !GameOverSurface || !HomeSurface || !PlayAgainSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Creating texture from surface
    AppleTexture = SDL_CreateTextureFromSurface( renderer, AppleSurface);
    PointerTexture = SDL_CreateTextureFromSurface( renderer, PointerSurface);
    GameOverTexture = SDL_CreateTextureFromSurface( renderer, GameOverSurface);
    HomeTexture = SDL_CreateTextureFromSurface( renderer, HomeSurface);
    PlayAgainTexture = SDL_CreateTextureFromSurface( renderer, PlayAgainSurface);

    // Checking if the texture was successfully created from surface
    if(!AppleTexture || !PointerTexture || !GameOverTexture || !HomeTexture || !PlayAgainTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(AppleSurface);
    SDL_FreeSurface(PointerSurface);
    SDL_FreeSurface(GameOverSurface);
    SDL_FreeSurface(HomeSurface);
    SDL_FreeSurface(PlayAgainSurface);

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
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,  "SDL_CreateColorCursor Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Setting the created cursor as the active cursor for the application
    SDL_SetCursor(Cursor);

    SDL_FreeSurface(CursorSurface);

    // Loading snake's image files

    // Green snake color
    GreenSnakeHeadSurface = IMG_Load("tools/images/snake/green/head.png");
    GreenSnakeBodySurface = IMG_Load("tools/images/snake/green/body.png");
    GreenSnakeCornerSurface = IMG_Load("tools/images/snake/green/corner.png");
    GreenSnakeTailSurface = IMG_Load("tools/images/snake/green/tail.png");
    // Blue snake color
    BlueSnakeHeadSurface = IMG_Load("tools/images/snake/blue/head.png");
    BlueSnakeBodySurface = IMG_Load("tools/images/snake/blue/body.png");
    BlueSnakeCornerSurface = IMG_Load("tools/images/snake/blue/corner.png");
    BlueSnakeTailSurface = IMG_Load("tools/images/snake/blue/tail.png");

    // Checking if the snake's image was successfully loaded
    if(!GreenSnakeHeadSurface || !GreenSnakeBodySurface || !GreenSnakeCornerSurface || !GreenSnakeTailSurface ||
       !BlueSnakeHeadSurface || !BlueSnakeBodySurface || !BlueSnakeCornerSurface || !BlueSnakeTailSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Creating texture from surface

    // Green snake color
    GreenSnakeHeadTexture = SDL_CreateTextureFromSurface( renderer, GreenSnakeHeadSurface);
    GreenSnakeBodyTexture = SDL_CreateTextureFromSurface( renderer, GreenSnakeBodySurface);
    GreenSnakeCornerTexture = SDL_CreateTextureFromSurface( renderer, GreenSnakeCornerSurface);
    GreenSnakeTailTexture = SDL_CreateTextureFromSurface( renderer, GreenSnakeTailSurface);

    // Blue snake color
    BlueSnakeHeadTexture = SDL_CreateTextureFromSurface( renderer, BlueSnakeHeadSurface);
    BlueSnakeBodyTexture = SDL_CreateTextureFromSurface( renderer, BlueSnakeBodySurface);
    BlueSnakeCornerTexture = SDL_CreateTextureFromSurface( renderer, BlueSnakeCornerSurface);
    BlueSnakeTailTexture = SDL_CreateTextureFromSurface( renderer, BlueSnakeTailSurface);

    // Checking if the texture was successfully created from surface
    if(!GreenSnakeHeadTexture || !GreenSnakeBodyTexture || !GreenSnakeCornerTexture || !GreenSnakeTailTexture ||
       !BlueSnakeHeadTexture || !BlueSnakeBodyTexture || !BlueSnakeCornerTexture || !BlueSnakeTailTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture

    // Green snake color
    SDL_FreeSurface(GreenSnakeHeadSurface);
    SDL_FreeSurface(GreenSnakeBodySurface);
    SDL_FreeSurface(GreenSnakeCornerSurface);
    SDL_FreeSurface(GreenSnakeTailSurface);

    // Blue snake color
    SDL_FreeSurface(BlueSnakeHeadSurface);
    SDL_FreeSurface(BlueSnakeBodySurface);
    SDL_FreeSurface(BlueSnakeCornerSurface);
    SDL_FreeSurface(BlueSnakeTailSurface);

    // Initialization of the SDL_ttf library
    if (TTF_Init() == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_Init Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Opening a font
    ScoreFont = TTF_OpenFont("tools/fonts/MinecraftRegularFont.TTF", 28);
    MenuFont = TTF_OpenFont("tools/fonts/TalkComic.TTF", 50);

    // Checking if the font was successfully openned
    if(!ScoreFont || !MenuFont)
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

    bool onSnake;

    // Generation of a random position of the apple within the window
    do
    {
        apple->position.x = (rand() % (WINDOW_WIDTH / SNAKE_SIZE)) * SNAKE_SIZE;
        apple->position.y = (rand() % (WINDOW_HEIGHT / SNAKE_SIZE)) * SNAKE_SIZE;

        onSnake = false;
        if(isHovering == onMode1)
        {
            // Checking if the apple is generated on the body of the snake in the first mode
            for( int i = 0; i < snake.size && !onSnake; i++)
                onSnake = (snake.chunk[i].position.x == apple->position.x) && (snake.chunk[i].position.y == apple->position.y);
        }
        else if (isHovering == onMode2)
        {
            // Checking if the apple is generated on the body of the first snake in the second mode
            for (int i = 0; i < snake1.size && !onSnake; i++)
                onSnake = (snake1.chunk[i].position.x == apple->position.x) && (snake1.chunk[i].position.y == apple->position.y);

            if (!onSnake)
            {
                // Checking if the apple is generated on the body of the second snake in the second mode
                for (int i = 0; i < snake2.size && !onSnake; i++)
                    onSnake = (snake2.chunk[i].position.x == apple->position.x) && (snake2.chunk[i].position.y == apple->position.y);
            }
        }

    } while(((apple->position.x >= 750 && apple->position.x < 790) && (apple->position.y >= 0 && apple->position.y < 40) && (isHovering == onMode1)) ||
            ((apple->position.x >= 360 && apple->position.x < 440) && (apple->position.y >= 0 && apple->position.y < 40) && (isHovering == onMode2)) ||
            onSnake);
}

void DrawApple(SDL_Renderer *renderer)
{
    // Rendering an image that is representing the apple
    SDL_Rect AppleCell = { apple.position.x, apple.position.y, SNAKE_SIZE, SNAKE_SIZE};
    SDL_RenderCopy( renderer, AppleTexture, NULL, &AppleCell);
}

void InitializeHighestScore(player *snake)
{
    snake->highestScore = -1;
}

void CreateSnake( player *snake, int initialX, int initialY)
{
    // Setting the snake to its initial parameters
    snake->size = SNAKE_INITIAL_SIZE, snake->score = 0, snake->highestScore = (snake->highestScore == -1)? 0: snake->highestScore, snake->state = true, snake->speed = 100;

    // Setting each chunk to its position
    for( int i = 0; i < snake->size; i++)
    {
        snake->chunk[i].position.x = initialX - i * SNAKE_SIZE;
        snake->chunk[i].position.y = initialY;
        snake->chunk[i].angle = 0;
        snake->chunk[i].direction = STABLE;
    }
}

void DrawSnake( player *snake, SDL_Renderer *renderer, SnakeColor color)
{
    SDL_Texture *head, *body, *corner, *tail;

    if(color == GREEN)
    {
        head = GreenSnakeHeadTexture;
        body = GreenSnakeBodyTexture;
        corner = GreenSnakeCornerTexture;
        tail = GreenSnakeTailTexture;
    }
    else if(color == BLUE)
    {
        head = BlueSnakeHeadTexture;
        body = BlueSnakeBodyTexture;
        corner = BlueSnakeCornerTexture;
        tail = BlueSnakeTailTexture;
    }

    for( int i = 0; i < snake->size; i++)
    {
        SDL_Rect SnakeSegment = { snake->chunk[i].position.x, snake->chunk[i].position.y, SNAKE_SIZE, SNAKE_SIZE};
        int previousDirection = snake->chunk[i+1].direction, currentDirection = snake->chunk[i].direction;

        if (i == 0) // Render snake head
            SDL_RenderCopyEx( renderer, head, NULL, &SnakeSegment, snake->chunk[i].angle, NULL, SDL_FLIP_NONE);
        else if (i == snake->size-1) // Render snake tail
            SDL_RenderCopyEx( renderer, tail, NULL, &SnakeSegment, snake->chunk[i].angle, NULL, SDL_FLIP_NONE);
        else if ((previousDirection == UP && currentDirection == RIGHT) || (previousDirection == LEFT && currentDirection == DOWN)) // Render snake corner
            SDL_RenderCopyEx( renderer, corner, NULL, &SnakeSegment, 0, NULL, SDL_FLIP_NONE);
        else if ((previousDirection == RIGHT && currentDirection == DOWN) || (previousDirection == UP && currentDirection == LEFT)) // Render snake corner
            SDL_RenderCopyEx( renderer, corner, NULL, &SnakeSegment, 90, NULL, SDL_FLIP_NONE);
        else if ((previousDirection == DOWN && currentDirection == LEFT) || (previousDirection == RIGHT && currentDirection == UP)) // Render snake corner
            SDL_RenderCopyEx( renderer, corner, NULL, &SnakeSegment, 180, NULL, SDL_FLIP_NONE);
        else if ((previousDirection == LEFT && currentDirection == UP) || (previousDirection == DOWN && currentDirection == RIGHT)) // Render snake corner
            SDL_RenderCopyEx( renderer, corner, NULL, &SnakeSegment, -90, NULL, SDL_FLIP_NONE);
        else // Render snake body
            SDL_RenderCopyEx( renderer, body, NULL, &SnakeSegment, snake->chunk[i].angle, NULL, SDL_FLIP_NONE);
    }
}

void MoveSnake(player *snake)
{
    // Check if the snake's head collides with its body
    for( int i = 1; i < snake->size && isHovering == onMode1; i++)
    {
        if(snake->chunk[0].position.x == snake->chunk[i].position.x && snake->chunk[0].position.y == snake->chunk[i].position.y && snake->score != 0)
        {
            if (snake->score > snake->highestScore) snake->highestScore = snake->score;
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

    // Shift the positions of snake chunks to follow the head
    for( int i = snake->size-1; i > 0 && snake->chunk[0].direction != STABLE; i--)
        snake->chunk[i] = snake->chunk[i-1]; // Assign the position of the previous chunk to the current chunk

    // Switch statement to handle snake movement based on its direction
    switch(snake->chunk[0].direction)
    {
        case STABLE:
            break;
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
}

void DrawScore( player *snake, SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, SDL_Color color, SDL_Rect rect)
{
    // Defining an array characters to store the score as a string
    char ScoreString[50];

    // Convert the integer score to a string using itoa
    itoa(snake->score, ScoreString, 10);

    // Render the score string onto a surface using the provided font and color
    surface = TTF_RenderText_Solid( ScoreFont, ScoreString, color);

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
    SDL_RenderCopy( renderer, texture, NULL, &rect);
}

void RenderMenuBackgroundImage(SDL_Renderer *renderer)
{
    // Load the image file into a surface
    SDL_Surface *surface = IMG_Load("tools/images/MenuBackground.png");

    // Checking if the surface was successfully loaded
    if(!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Create a texture from the surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, surface);

    // Checking if the texture was successfully created
    if(!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Freeing the surface after creating the texture
    SDL_FreeSurface(surface);

    // Render the texture onto the renderer
    SDL_RenderCopy( renderer, texture, NULL, NULL);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}

void RenderCreator( SDL_Renderer *renderer, char Creator[])
{
    // Defining a string to store the text "Created by: Creator"
    char CreatorString[100];

    // Copy the text "Created by: Creator" to the string CreatorString using the sprintf function
    sprintf(CreatorString, "Created by: %s", Creator);

    // Render the text "Created by: Youness SBAI" using the provided font and color
    SDL_Surface *CreatedBySurface = TTF_RenderText_Solid( MenuFont, CreatorString, (SDL_Color){ 179, 59, 0, 255});

    // Checking if the surface was successfully created
    if(!CreatedBySurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create a texture from the surface
    SDL_Texture *CreatedByTexture = SDL_CreateTextureFromSurface( renderer, CreatedBySurface);

    // Checking if the texture was successfully created
    if(!CreatedByTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(CreatedBySurface);

    // Render the texture onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, CreatedByTexture, NULL, &(SDL_Rect){ 20, 420, 360, 80});

    // Destroy the texture
    SDL_DestroyTexture(CreatedByTexture);
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
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle keyboard input
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            if(isHovering == onStart)
                                isHovering = onExit;
                            else if(isHovering == onExit)
                                isHovering = onStart;
                            else
                                isHovering = onStart;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_DOWN:
                            if(isHovering == onStart)
                                isHovering = onExit;
                            else if(isHovering == onExit)
                                isHovering = onStart;
                            else
                                isHovering = onExit;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_RETURN:
                            if(isHovering == onStart)
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MODE;
                            }
                            else if(isHovering == onExit)
                            {
                                MenuOption = EXIT;
                            }
                            break;
                    }
                }
                break;

            // This case is related to mouse motions
            case SDL_MOUSEMOTION:
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Extract the x and y coordinates of the mouse pointer from the event
                    int mouseX = event.motion.x, mouseY = event.motion.y;

                    if(mouseX >= 280 && mouseX <= 500 && mouseY >= 150 && mouseY <= 230) // Mouse is hovering start button
                    {
                        if(isHovering != onStart)
                        {
                            isHovering = onStart;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if(mouseX >= 280 && mouseX <= 500 && mouseY >= 240 && mouseY <= 320) // Mouse is hovering exit button
                    {
                        if (isHovering != onExit)
                        {
                            isHovering = onExit;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else // Mouse is hovering any button
                        isHovering = onNothing;
                }
                break;

            // If a mouse button is released
            case SDL_MOUSEBUTTONUP:
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle mouse input
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            int mouseX = event.button.x, mouseY = event.button.y;

                            if(mouseX >= 280 && mouseX <= 500 && mouseY >= 150 && mouseY <= 230) // If the user pressed start
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MODE;
                            }
                            else if(mouseX >= 280 && mouseX <= 500 && mouseY >= 240 && mouseY <= 320) // If the user pressed exit
                            {
                                MenuOption = EXIT;
                            }
                            break;
                    }
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

    RenderMenuBackgroundImage(renderer);

    RenderCreator( renderer , "Youness SBAI");

    // Setting colors for the game title and the buttons
    SDL_Color DefaultColor = { 160, 160, 160, 255}, HoveringColor = { 0, 153, 76, 255};

    // Render the texts onto surfaces using the provided fonts and colors
    SDL_Surface *TitleSurface = TTF_RenderText_Solid( MenuFont, "Snake Game", (SDL_Color){ 0, 0, 0, 255});
    SDL_Surface *StartSurface = TTF_RenderText_Solid( MenuFont, "Start", (isHovering != onStart)? DefaultColor: HoveringColor);
    SDL_Surface *ExitSurface = TTF_RenderText_Solid( MenuFont, "Exit", (isHovering != onExit)? DefaultColor: HoveringColor);

    // Checking if the texts were successfully rendered
    if(!TitleSurface || !StartSurface || !ExitSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create textures from the rendered surfaces
    SDL_Texture *TitleTexture = SDL_CreateTextureFromSurface( renderer, TitleSurface);
    SDL_Texture *StartTexture = SDL_CreateTextureFromSurface( renderer, StartSurface);
    SDL_Texture *ExitTexture = SDL_CreateTextureFromSurface( renderer, ExitSurface);

    // Checking if the textures were successfully created
    if(!TitleTexture || !StartTexture || !ExitTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surfaces after they are no longer needed
    SDL_FreeSurface(TitleSurface);
    SDL_FreeSurface(StartSurface);
    SDL_FreeSurface(ExitSurface);

    // Rendering the textures onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, TitleTexture, NULL, &(SDL_Rect){ 100, 20, 600, 100});
    SDL_RenderCopy( renderer, StartTexture, NULL, &(SDL_Rect){ 280, 150, 220, 80});
    SDL_RenderCopy( renderer, ExitTexture, NULL, &(SDL_Rect){ 280, 240, 220, 80});

    switch(isHovering)
    {
        case onStart:
            SDL_RenderCopy( renderer, PointerTexture, NULL, &(SDL_Rect){ 220, 170, 50, 40});
            break;

        case onExit:
            SDL_RenderCopy( renderer, PointerTexture, NULL, &(SDL_Rect){ 220, 260, 50, 40});
    }

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Destroy the textures used in the menu
    SDL_DestroyTexture(TitleTexture);
    SDL_DestroyTexture(StartTexture);
    SDL_DestroyTexture(ExitTexture);
}

void HandleModeInput()
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
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle keyboard input
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            if(isHovering == onMode1)
                                isHovering = onMode2;
                            else if(isHovering == onMode2)
                                isHovering = onMode1;
                            else
                                isHovering = onMode1;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_DOWN:
                            if(isHovering == onMode1)
                                isHovering = onMode2;
                            else if(isHovering == onMode2)
                                isHovering = onMode1;
                            else
                                isHovering = onMode2;

                            Mix_PlayMusic( ClickingPopMusic, 0);
                            break;
                        case SDLK_RETURN:
                            if(isHovering == onMode1 || isHovering == onMode2)
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = START;
                            }
                            break;
                    }
                }
                break;

            // This case is related to mouse motions
            case SDL_MOUSEMOTION:
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Extract the x and y coordinates of the mouse pointer from the event
                    int mouseX = event.motion.x, mouseY = event.motion.y;

                    if(mouseX >= 10 && mouseX <= 60 && mouseY >= 10 && mouseY <= 60) // Mouse is hovering the return button
                    {
                        if(isHovering != onReturn)
                        {
                            isHovering = onReturn;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if(mouseX >= 325 && mouseX <= 475 && mouseY >= 150 && mouseY <= 220) // Mouse is hovering the first mode
                    {
                        if(isHovering != onMode1)
                        {
                            isHovering = onMode1;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if(mouseX >= 325 && mouseX <= 475 && mouseY >= 240 && mouseY <= 310) // Mouse is hovering the second mode
                    {
                        if (isHovering != onMode2)
                        {
                            isHovering = onMode2;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else // Mouse is hovering any button
                        isHovering = onNothing;
                }
                break;

            // If a mouse button is released
            case SDL_MOUSEBUTTONUP:
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle mouse input
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            int mouseX = event.button.x, mouseY = event.button.y;

                            if(mouseX >= 10 && mouseX <= 60 && mouseY >= 10 && mouseY <= 60) // Mouse is hovering the return button
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MENU;
                            }
                            else if(mouseX >= 325 && mouseX <= 475 && mouseY >= 150 && mouseY <= 220) // If the user pressed the first mode
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = START;
                            }
                            else if(mouseX >= 325 && mouseX <= 475 && mouseY >= 240 && mouseY <= 310) // If the user pressed the second mode
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = START;
                            }
                            break;
                    }
                }
                break;
        }
    }
}

void RenderMode(SDL_Renderer *renderer)
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

    RenderMenuBackgroundImage(renderer);

    RenderCreator( renderer , "Youness SBAI");

    // Loading an image from the file
    SDL_Surface *returnSurface = IMG_Load("tools/images/return.png");

    // Checking if the image was successfully loaded
    if(!returnSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Load Error: %s\n", IMG_GetError());
        QuitSDL();
    }

    // Creating a texture from the surface
    SDL_Texture *returnTexture = SDL_CreateTextureFromSurface(renderer, returnSurface);

    // Checking if the texture was successfully created
    if(!returnTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Freeing the surface after creating the texture
    SDL_FreeSurface(returnSurface);

    // Setting colors for the game title and the buttons
    SDL_Color DefaultColor = { 160, 160, 160, 255};

    // Render the texts onto surfaces using the provided fonts and colors
    SDL_Surface *ModeSurface = TTF_RenderText_Solid( MenuFont, "Choose the game mode:", (SDL_Color){ 0, 51, 102, 255});
    SDL_Surface *Mode1Surface = TTF_RenderText_Solid( MenuFont, "1 Player", (isHovering != onMode1)? DefaultColor: (SDL_Color){ 0, 0, 255, 255});
    SDL_Surface *Mode2Surface = TTF_RenderText_Solid( MenuFont, "1v1", (isHovering != onMode2)? DefaultColor: (SDL_Color){ 255, 0, 0, 255});

    // Checking if the texts were successfully rendered
    if(!ModeSurface || !Mode1Surface || !Mode2Surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create textures from the rendered surfaces
    SDL_Texture *ModeTexture = SDL_CreateTextureFromSurface( renderer, ModeSurface);
    SDL_Texture *Mode1Texture = SDL_CreateTextureFromSurface( renderer, Mode1Surface);
    SDL_Texture *Mode2Texture = SDL_CreateTextureFromSurface( renderer, Mode2Surface);

    // Checking if the textures were successfully created
    if(!ModeTexture || !Mode1Texture || !Mode2Texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    SDL_FreeSurface(ModeSurface);
    SDL_FreeSurface(Mode1Surface);
    SDL_FreeSurface(Mode2Surface);

    SDL_RenderCopy( renderer, returnTexture, NULL, (isHovering != onReturn)? &(SDL_Rect){ 10, 10, 50, 50}: &(SDL_Rect){ 5, 5, 60, 60});

    // Rendering the textures onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, ModeTexture, NULL, &(SDL_Rect){ 175, 50, 450, 85});
    SDL_RenderCopy( renderer, Mode1Texture, NULL, &(SDL_Rect){ 325, 150, 150, 70});
    SDL_RenderCopy( renderer, Mode2Texture, NULL, &(SDL_Rect){ 325, 240, 150, 70});

    switch(isHovering)
    {
        case onMode1:
            SDL_RenderCopy( renderer, PointerTexture, NULL, &(SDL_Rect){ 265, 170, 50, 35});
            break;

        case onMode2:
            SDL_RenderCopy( renderer, PointerTexture, NULL, &(SDL_Rect){ 265, 260, 50, 35});
    }

    // Present the renderer
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(returnTexture);

    // Destroy the textures used in the game modes
    SDL_DestroyTexture(ModeTexture);
    SDL_DestroyTexture(Mode1Texture);
    SDL_DestroyTexture(Mode2Texture);
}

void HandleMode1Input(player *snake)
{
    // ensuring that the direction can only be changed once per frame
    bool directionChanged = false;

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
                if(directionChanged) break;

                // Handle keyboard input
                switch(event.key.keysym.sym)
                {
                    case SDLK_z:
                    case SDLK_UP:
                        if(snake->chunk[0].direction != DOWN)
                        {
                            snake->chunk[0].direction = UP;
                            snake->chunk[0].angle = -90;
                            directionChanged = true;
                        }
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        if(snake->chunk[0].direction != LEFT)
                        {
                            snake->chunk[0].direction = RIGHT;
                            snake->chunk[0].angle = 0;
                            directionChanged = true;
                        }
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        if(snake->chunk[0].direction != UP)
                        {
                            snake->chunk[0].direction = DOWN;
                            snake->chunk[0].angle = 90;
                            directionChanged = true;
                        }
                        break;
                    case SDLK_q:
                    case SDLK_LEFT:
                        if(snake->chunk[0].direction != RIGHT)
                        {
                            snake->chunk[0].direction = LEFT;
                            snake->chunk[0].angle = 180;
                            directionChanged = true;
                        }
                        break;
                }
                break;
        }
    } directionChanged = false;
}

void RenderMode1(SDL_Renderer *renderer)
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
    DrawSnake( &snake, renderer, GREEN);
    DrawScore( &snake, renderer, ScoreSurface, ScoreTexture, (SDL_Color){ 255, 255, 255, 255}, (SDL_Rect){ 750, 0, 40, 40});

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay(snake.speed);
}

void HandleMode2Input( player *snake1, player *snake2)
{
    // ensuring that the direction can only be changed once per frame
    bool direction1Changed = false, direction2Changed = false;

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
                    // Input handling for the player number 1
                    case SDLK_UP:
                        if(!direction1Changed && snake1->chunk[0].direction != DOWN)
                        {
                            snake1->chunk[0].direction = UP;
                            snake1->chunk[0].angle = -90;
                            direction1Changed = true;
                        }
                        break;
                    case SDLK_RIGHT:
                        if(!direction1Changed && snake1->chunk[0].direction != LEFT)
                        {
                            snake1->chunk[0].direction = RIGHT;
                            snake1->chunk[0].angle = 0;
                            direction1Changed = true;
                        }
                        break;
                    case SDLK_DOWN:
                        if(!direction1Changed && snake1->chunk[0].direction != UP)
                        {
                            snake1->chunk[0].direction = DOWN;
                            snake1->chunk[0].angle = 90;
                            direction1Changed = true;
                        }
                        break;
                    case SDLK_LEFT:
                        if(!direction1Changed && snake1->chunk[0].direction != RIGHT)
                        {
                            snake1->chunk[0].direction = LEFT;
                            snake1->chunk[0].angle = 180;
                            direction1Changed = true;
                        }
                        break;

                    // Input handling for the player number 2
                    case SDLK_z:
                        if(!direction2Changed && snake2->chunk[0].direction != DOWN)
                        {
                            snake2->chunk[0].direction = UP;
                            snake2->chunk[0].angle = -90;
                            direction2Changed = true;
                        }
                        break;
                    case SDLK_d:
                        if(!direction2Changed && snake2->chunk[0].direction != LEFT)
                        {
                            snake2->chunk[0].direction = RIGHT;
                            snake2->chunk[0].angle = 0;
                            direction2Changed = true;
                        }
                        break;
                    case SDLK_s:
                        if(!direction2Changed && snake2->chunk[0].direction != UP)
                        {
                            snake2->chunk[0].direction = DOWN;
                            snake2->chunk[0].angle = 90;
                            direction2Changed = true;
                        }
                        break;
                    case SDLK_q:
                        if(!direction2Changed && snake2->chunk[0].direction != RIGHT)
                        {
                            snake2->chunk[0].direction = LEFT;
                            snake2->chunk[0].angle = 180;
                            direction2Changed = true;
                        }
                        break;
                }
                break;
        }
    } direction1Changed = false; direction2Changed = false;
}

void RenderMode2(SDL_Renderer *renderer)
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
    MoveSnake(&snake1), MoveSnake(&snake2);
    DrawSnake( &snake1, renderer, GREEN), DrawSnake( &snake2, renderer, BLUE);
    DrawScore( &snake1, renderer, ScoreSurface, ScoreTexture, (SDL_Color){ 0, 255, 0, 255}, (SDL_Rect){ 360, 0, 40, 40}), DrawScore( &snake2, renderer, ScoreSurface, ScoreTexture, (SDL_Color){ 0, 0, 255, 255}, (SDL_Rect){ 400, 0, 40, 40});

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay((snake1.speed < snake2.speed)? snake1.speed: snake2.speed);
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

            // If a key is pressed
            case SDL_KEYDOWN:
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle keyboard input
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_RIGHT:
                            if (isHovering != onPlayAgain)
                            {
                                isHovering = onPlayAgain;
                                Mix_PlayMusic( ClickingPopMusic, 0);
                            }
                            break;
                        case SDLK_LEFT:
                            if (isHovering != onHome)
                            {
                                isHovering = onHome;
                                Mix_PlayMusic( ClickingPopMusic, 0);
                            }
                            break;
                        case SDLK_RETURN:
                            if(isHovering == onHome || isHovering == onPlayAgain)
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = (isHovering == onHome)? MENU: (isHovering == onPlayAgain)? START: isHovering;
                            }
                            break;
                    }
                }
                break;

            // This case is related to mouse motions
            case SDL_MOUSEMOTION:
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Extract the x and y coordinates of the mouse pointer from the event
                    int mouseX = event.motion.x, mouseY = event.motion.y;

                    if(mouseX >= 290 && mouseX <= 360 && mouseY >= 300 && mouseY <= 370) // Mouse is hovering home button
                    {
                        if(isHovering != onHome)
                        {
                            isHovering = onHome;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else if(mouseX >= 440 && mouseX <= 510 && mouseY >= 300 && mouseY <= 370) // Mouse is hovering play again button
                    {
                        if (isHovering != onPlayAgain)
                        {
                            isHovering = onPlayAgain;
                            Mix_PlayMusic( ClickingPopMusic, 0);
                        }
                    }
                    else // Mouse is hovering any button
                        isHovering = onNothing;
                }
                break;

            // If a mouse button is released
            case SDL_MOUSEBUTTONUP:
                if(!Mix_PlayingMusic()) // Ignore input if the music is still playing
                {
                    // Handle mouse input
                    switch(event.button.button)
                    {
                        case SDL_BUTTON_LEFT:
                            int mouseX = event.button.x, mouseY = event.button.y;

                            if(mouseX >= 290 && mouseX <= 360 && mouseY >= 300 && mouseY <= 370) // If the user pressed home
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = MENU;
                            }
                            else if(mouseX >= 440 && mouseX <= 510 && mouseY >= 300 && mouseY <= 370) // If the user pressed play again
                            {
                                Mix_HaltMusic();
                                Mix_PlayMusic( ClickingMusic, 0);
                                MenuOption = START;
                            }
                            break;
                    }
                }
                break;
        }
    }
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

    // Rendering the game over texture onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, GameOverTexture, NULL, &(SDL_Rect){ 150, 40, 500, 80});

    // Defining an array of characters to srore the final score as a string
    char FinalScoreString[60], HighestScoreString[60];

    // Convert the integer score to a string using sprintf
    sprintf( FinalScoreString, "Final Score: %d", snake.score);
    sprintf( HighestScoreString, "Highest Score: %d", snake.highestScore);

    // Render the game over visuals onto a surface using the provided font and color
    SDL_Surface *FinalScoreSurface = TTF_RenderText_Solid( MenuFont, FinalScoreString, (SDL_Color){ 255, 255, 255, 255});
    SDL_Surface *HighestScoreSurface = TTF_RenderText_Solid( MenuFont, HighestScoreString, (SDL_Color){ 255, 255, 255, 255});

    // Checking if the text was successfully rendered
    if(!FinalScoreSurface || !HighestScoreSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create a texture from the rendered surface
    SDL_Texture *FinalScoreTexture = SDL_CreateTextureFromSurface( renderer, FinalScoreSurface);
    SDL_Texture *HighestScoreTexture = SDL_CreateTextureFromSurface( renderer, HighestScoreSurface);

    // Checking if the texture was successfully created
    if(!FinalScoreTexture || !HighestScoreTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(FinalScoreSurface);
    SDL_FreeSurface(HighestScoreSurface);

    // Rendering the texture onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, FinalScoreTexture, NULL, &(SDL_Rect){ 250, 160, 300, 60});
    SDL_RenderCopy( renderer, HighestScoreTexture, NULL, &(SDL_Rect){ 540, 440, 250, 60});
    SDL_RenderCopy( renderer, HomeTexture, NULL, (isHovering != onHome)? &(SDL_Rect){ 290, 300, 70, 70}: &(SDL_Rect){ 285, 295, 80, 80});
    SDL_RenderCopy( renderer, PlayAgainTexture, NULL, (isHovering != onPlayAgain)? &(SDL_Rect){ 440, 300, 70, 70}: &(SDL_Rect){ 435, 295, 80, 80});

    // Presenting the renderer
    SDL_RenderPresent(renderer);

    // Destroy the textures used in the game over
    SDL_DestroyTexture(FinalScoreTexture);
    SDL_DestroyTexture(HighestScoreTexture);
}

void QuitSDL()
{
    if(ScoreTexture)
        SDL_DestroyTexture(ScoreTexture);
    if(MenuFont)
        TTF_CloseFont(MenuFont);
    if(ScoreFont)
        TTF_CloseFont(ScoreFont);
    TTF_Quit();
    if(BlueSnakeTailTexture)
        SDL_DestroyTexture(BlueSnakeTailTexture);
    if(BlueSnakeCornerTexture)
        SDL_DestroyTexture(BlueSnakeCornerTexture);
    if(BlueSnakeBodyTexture)
        SDL_DestroyTexture(BlueSnakeBodyTexture);
    if(BlueSnakeHeadTexture)
        SDL_DestroyTexture(BlueSnakeHeadTexture);
    if(GreenSnakeTailTexture)
        SDL_DestroyTexture(GreenSnakeTailTexture);
    if(GreenSnakeCornerTexture)
        SDL_DestroyTexture(GreenSnakeCornerTexture);
    if(GreenSnakeBodyTexture)
        SDL_DestroyTexture(GreenSnakeBodyTexture);
    if(GreenSnakeHeadTexture)
        SDL_DestroyTexture(GreenSnakeHeadTexture);
    if(Cursor)
        SDL_FreeCursor(Cursor);
    if(PlayAgainTexture)
        SDL_DestroyTexture(PlayAgainTexture);
    if(HomeTexture)
        SDL_DestroyTexture(HomeTexture);
    if(GameOverTexture)
        SDL_DestroyTexture(GameOverTexture);
    if(PointerTexture)
        SDL_DestroyTexture(PointerTexture);
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