#pragma once

#include "sdl_utils.h"

// Function used to handle the input of the menu
void HandleMenuInput();

// Function used to handle the input of the mode selection screen
void HandleModeInput();

// Function used to handle the input of the game in mode 1
void HandleMode1Input(player *snake);

// Function used to handle the input of the game in mode 2
void HandleMode2Input( player *snake1, player *snake2);

// Function used to handle the input of the game over screen
void HandleGameOverInput();



// Function used to render the background image of the menu
void RenderMenuBackgroundImage(SDL_Renderer *renderer);

// Function used to render the creator of the game
void RenderCreator( SDL_Renderer *renderer, char Creator[]);

// Function used to render the menu
void RenderMenu(SDL_Renderer *renderer);

// Function used to render the mode selection screen
void RenderMode(SDL_Renderer *renderer);

// Function used to render the game in mode 1
void RenderMode1(SDL_Renderer *renderer);

// Function used to render the game in mode 2
void RenderMode2( SDL_Renderer *renderer, int *countDown, int *startTime);

// Function used to render the game over screen
void RenderGameOver(SDL_Renderer *renderer);