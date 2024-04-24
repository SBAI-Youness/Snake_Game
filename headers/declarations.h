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
} fruit;

typedef struct
{
    int direction;
    coordinates position;
} segments;

typedef struct
{
    int score, size;
    bool state;
    segments chunk[10000];
} player;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *IconSurface = NULL;
Mix_Music *SnakeEats = NULL;

player snake;
fruit apple;

bool quit = false;

// Function used to initialize the SDL2 library
void InitSDL();

// Function used to create the apple
void CreateApple(fruit *apple);

// Function used to draw the apple
void DrawApple( SDL_Renderer *renderer, fruit *apple);

// Function used to create the snake
void CreateSnake(player *snake);

// Function used to draw the snake in the window
void DrawSnake( SDL_Renderer *renderer, player *snake);

// Function used to move the snake
void MoveSnake(player *snake);

// Function used to handle user input
void HandleInput(player *snake);

// Function used for rendering
void Render(SDL_Renderer *renderer);

// Function used to quit the SDL2 library
void QuitSDL();