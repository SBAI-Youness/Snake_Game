#pragma once

// Header file definitions
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Window definitions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

// Snake definitions
#define SNAKE_INITIAL_SIZE 3
#define SNAKE_SIZE 20

// Star definition
#define NUMBER_OF_STARS 400

// Menu's options enumeration
typedef enum{ MENU, START, EXIT, MODE, GAMEOVER} GameState;

// Button's state enumeration
typedef enum{ onNothing, onStart, onExit, onMode1, onMode2, onHome, onPlayAgain} MouseHoveringState;

// Direction enumerations
typedef enum{ STABLE, UP, RIGHT, DOWN, LEFT} Direction;

typedef struct
{
    int x, y;
} coordinates;

typedef struct
{
    coordinates position;
    float velocity, depth;
} star;

typedef struct
{
    coordinates position;
} fruit;

typedef struct
{
    Direction direction;
    double angle;
    coordinates position;
} segments;

typedef struct
{
    int score, highestScore, size;
    float speed;
    bool state;
    segments chunk[999];
} player;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Surface *IconSurface, *AppleSurface, *ScoreSurface, *CursorSurface, *PointerSurface, *GameOverSurface, *SnakeHeadSurface, *SnakeBodySurface, *SnakeCornerSurface, *SnakeTailSurface, *MenuBackgroundSurface, *HomeSurface, *PlayAgainSurface;
extern SDL_Texture *AppleTexture, *ScoreTexture, *PointerTexture, *GameOverTexture, *SnakeHeadTexture, *SnakeBodyTexture, *SnakeCornerTexture, *SnakeTailTexture, *MenuBackgroundTexture, *HomeTexture, *PlayAgainTexture;
extern SDL_Cursor *Cursor;
extern Mix_Music *EatingMusic, *ClickingMusic, *ClickingPopMusic, *GameOverMusic;
extern TTF_Font *ScoreFont, *MenuFont;

extern player snake, snake1, snake2;
extern fruit apple;
extern star stars[NUMBER_OF_STARS];

extern bool quit;

extern GameState MenuOption;

extern MouseHoveringState isHovering;

// Function used to initialize the SDL2 library
void InitSDL();

// Function used to create the stars
void CreateStars(star stars[]);

// Function used to update and draw the stars
void UpdateAndDrawStars( SDL_Renderer *renderer, star stars[]);

// Function used to create the apple
void CreateApple(fruit *apple);

// Function used to draw the apple
void DrawApple(SDL_Renderer *renderer);

// Function used to intialize the highest score of the snake
void InitializeHighestScore(player *snake);

// Function used to create the snake
void CreateSnake( player *snake, int initialX, int initialY);

// Function used to draw the snake in the window
void DrawSnake( player *snake, SDL_Renderer *renderer);

// Function used to move the snake
void MoveSnake(player *snake);

// Function used to show the score in the window
void DrawScore( player *snake, SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, SDL_Color color, SDL_Rect rect);

// Function used to handle user input while the menu is shown
void HandleMenuInput();

// Function used to draw the menu
void RenderMenu(SDL_Renderer *renderer);

// Function used to handle user input while the modes are shown
void HandleModeInput();

// Function used to draw the modes
void RenderMode(SDL_Renderer *renderer);

// Function used to handle user input while playing in the first mode
void HandleMode1Input(player *snake);

// Function used for rendering the first mode
void RenderMode1(SDL_Renderer *renderer);

// Function used to handle user input while playing in the second mode
void HandleMode2Input( player *snake1, player *snake2);

// Function used for rendering the second mode
void RenderMode2(SDL_Renderer *renderer);

// Function used to handle the user input while he is in the game over
void HandleGameOverInput();

// Function used to draw the game over
void RenderGameOver(SDL_Renderer *renderer);

// Function used to quit the SDL2 library
void QuitSDL();