#include "headers\sdl_utils.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Cursor *Cursor = NULL;
Mix_Music *EatingMusic = NULL, *ClickingMusic = NULL, *ClickingPopMusic = NULL, *GameOverMusic = NULL;
TTF_Font *font28 = NULL, *font50 = NULL;

player snake, snake1, snake2;
fruit apple;
star stars[NUMBER_OF_STARS];

SDL_Surface *IconSurface = NULL, *AppleSurface = NULL, *CursorSurface = NULL, *PointerSurface = NULL, *GameOverSurface = NULL, *GreenSnakeHeadSurface = NULL, *GreenSnakeBodySurface = NULL, *GreenSnakeCornerSurface = NULL, *GreenSnakeTailSurface = NULL, *BlueSnakeHeadSurface = NULL, *BlueSnakeBodySurface = NULL, *BlueSnakeCornerSurface = NULL, *BlueSnakeTailSurface = NULL, *HomeSurface = NULL, *PlayAgainSurface = NULL;
SDL_Texture *AppleTexture = NULL, *PointerTexture = NULL, *GameOverTexture = NULL, *GreenSnakeHeadTexture = NULL, *GreenSnakeBodyTexture = NULL, *GreenSnakeCornerTexture = NULL, *GreenSnakeTailTexture = NULL, *BlueSnakeHeadTexture = NULL, *BlueSnakeBodyTexture = NULL, *BlueSnakeCornerTexture = NULL, *BlueSnakeTailTexture = NULL, *HomeTexture = NULL, *PlayAgainTexture = NULL;

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
    font28 = TTF_OpenFont("tools/fonts/MinecraftRegularFont.TTF", 28);
    font50 = TTF_OpenFont("tools/fonts/TalkComic.TTF", 50);

    // Checking if the font was successfully openned
    if(!font28 || !font50)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_OpenFont Error: %s\n", TTF_GetError());
        QuitSDL();
    }
}

void QuitSDL()
{
    if(font50)
        TTF_CloseFont(font50);
    if(font28)
        TTF_CloseFont(font28);
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