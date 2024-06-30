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
void HandleGameOverMode1Input();