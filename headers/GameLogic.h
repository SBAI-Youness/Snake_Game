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
#define SNAKE_INITIAL_SIZE 4
#define SNAKE_SIZE 20

// Star definition
#define NUMBER_OF_STARS 400

// Menu's options enumeration
typedef enum{ MENU, START, EXIT} GameState; // 0 --> show the menu || 1 --> start the game || 2 --> exit the game

// Direction definitions
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

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
    int direction;
    coordinates position;
} segments;

typedef struct
{
    int score, size;
    float speed;
    bool state;
    segments chunk[10000];
} player;

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Surface *IconSurface, *AppleSurface, *ScoreSurface, *TitleSurface, *StartSurface, *ExitSurface, *CursorSurface, *MenuBackgroundSurface;
extern SDL_Texture *AppleTexture, *ScoreTexture, *TitleTexture, *StartTexture, *ExitTexture, *MenuBackgroundTexture;
extern SDL_Cursor *Cursor;
extern Mix_Music *EatingMusic, *ClickingMusic, *RainMusic;
extern TTF_Font *ScoreFont, *MenuFont;

extern player snake;
extern fruit apple;
extern star stars[NUMBER_OF_STARS];

extern bool quit;

extern GameState MenuOption;

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

// Function used to create the snake
void CreateSnake(player *snake);

// Function used to draw the snake in the window
void DrawSnake(SDL_Renderer *renderer);

// Function used to move the snake
void MoveSnake(player *snake);

// Function used to handle user input while playing
void HandleGameInput(player *snake);

// Function used to draw the menu
void RenderMenu(SDL_Renderer *renderer);

// Function used to handle user input while the menu is shown
void HandleMenuInput();

// Function used to show the score in the window
void DrawScore( SDL_Renderer *renderer, SDL_Surface *surface, SDL_Texture *texture, TTF_Font *font);

// Function used for rendering
void RenderGame(SDL_Renderer *renderer);

// Function used to quit the SDL2 library
void QuitSDL();