#pragma once

#include "sdl_utils.h"

// Function used to render the background image of the menu
void RenderMenuBackgroundImage(SDL_Renderer *renderer);

// Function used to render the creator of the game
void RenderCreator( SDL_Renderer *renderer, char Creator[]);

// Function used to render the player's number
void RenderPlayer( SDL_Renderer *renderer, const char *playerNumber, SDL_Rect rect);

// Function used to render the menu
void RenderMenu(SDL_Renderer *renderer);

// Function used to render the mode selection screen
void RenderMode(SDL_Renderer *renderer);

// Function used to render the game in mode 1
void RenderMode1(SDL_Renderer *renderer);

// Function used to render the game in mode 2
void RenderMode2( SDL_Renderer *renderer, int *countDown, int *startTime);

// Function used to render the game over screen in the first mode
void RenderGameOverMode1(SDL_Renderer *renderer);

// Function used to render the game over screen in the second mode
void RenderGameOverMode2(SDL_Renderer *renderer);