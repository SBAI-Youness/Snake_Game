#pragma once

#include "sdl_utils.h"

// Function used to create the stars
void CreateStars(star stars[]);

// Function used to update and draw the stars
void UpdateAndDrawStars( SDL_Renderer *renderer, star stars[]);

// Function used to create the apple
void CreateApple(fruit *apple);

// Function used to draw the apple
void DrawApple(SDL_Renderer *renderer);

// Function used to initialize the highest score
void InitializeHighestScore(player *snake);

// Function used to create the snake
void CreateSnake( player *snake, int initialX, int initialY);

// Function used to draw the snake
void DrawSnake( player *snake, SDL_Renderer *renderer, SnakeColor color);

// Function used to move the snake
void MoveSnake(player *snake);

// Function used to show the score in the window
void DrawScore( player *snake, SDL_Renderer *renderer, SDL_Color color, SDL_Rect rect);

// Function used to show the countdown in the second mode
void RenderCountdown( SDL_Renderer *renderer, const char *text, SDL_Color color, SDL_Rect rect);