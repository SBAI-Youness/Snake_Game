#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

#define SNAKE_INITIAL_SIZE 4
#define SNAKE_SIZE 20

#define GRID_ROWS_SIZE (WINDOW_HEIGHT / SNAKE_SIZE)
#define GRID_COLUMNS_SIZE (WINDOW_WIDTH / SNAKE_SIZE)

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *IconSurface = NULL;

bool quit = false;

void InitSDL();
void DrawGrid(SDL_Renderer *renderer);
void HandleInput();
void Render(SDL_Renderer *renderer);
void QuitSDL();