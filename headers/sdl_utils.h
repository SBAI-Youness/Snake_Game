#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

#define SNAKE_INITIAL_SIZE 3
#define SNAKE_SIZE 20

#define NUMBER_OF_STARS 400

typedef enum { MENU, START, EXIT, MODE, GAMEOVER1, GAMEOVER2} GameState;

typedef enum { NONE, MODE_SINGLE_PLAYER, MODE_TWO_PLAYERS} GameMode;

typedef enum { onNothing, onStart, onExit, onReturn, onMode1, onMode2, onHome, onPlayAgain} MouseHoveringState;

typedef enum { GREEN, BLUE} SnakeColor;

typedef enum { STABLE, UP, RIGHT, DOWN, LEFT} Direction;

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
extern SDL_Cursor *Cursor;
extern Mix_Chunk *EatingMusic, *BeepMusic;
extern Mix_Music *ClickingMusic, *ClickingPopMusic, *GameOverMusic;
extern TTF_Font *font28, *font32, *font50;

extern player snake, snake1, snake2;
extern fruit apple;
extern star *stars;

extern SDL_Surface *IconSurface, *AppleSurface, *CursorSurface, *PointerSurface, *GameOverSurface, *GreenSnakeHeadSurface, *GreenSnakeBodySurface, *GreenSnakeCornerSurface, *GreenSnakeTailSurface, *BlueSnakeHeadSurface, *BlueSnakeBodySurface, *BlueSnakeCornerSurface, *BlueSnakeTailSurface, *HomeSurface, *PlayAgainSurface, *winnerSurface;
extern SDL_Texture *AppleTexture, *PointerTexture, *GameOverTexture, *GreenSnakeHeadTexture, *GreenSnakeBodyTexture, *GreenSnakeCornerTexture, *GreenSnakeTailTexture, *BlueSnakeHeadTexture, *BlueSnakeBodyTexture, *BlueSnakeCornerTexture, *BlueSnakeTailTexture, *HomeTexture, *PlayAgainTexture, *winnerTexture;

extern bool quit; // Variable used to check if the user wants to quit the game

extern GameState MenuOption; // Variable used to check the current menu option

extern MouseHoveringState isHovering; // Variable used to check if the mouse is hovering over a button

extern SnakeColor color;

// Function used to initialize the SDL2 library
void InitSDL();

// Function used to quit the SDL2 library
void QuitSDL();