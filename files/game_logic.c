#include "../headers/game_logic.h"

void CreateStars(star stars[])
{
    // Loop through each star
    for ( int i = 0; i < NUMBER_OF_STARS; i++)
    {
        // Generation of a random position of the star within the window
        stars[i].position.x = rand() % WINDOW_WIDTH;
        stars[i].position.y = rand() % WINDOW_HEIGHT;

        // Set the velocity (speed) of the star to a random value between 1 and 6
        stars[i].velocity = ((float)rand() / RAND_MAX) * 5 + 1;

        // Set the depth of the star to a random value between 0 and 1000
        stars[i].depth = ((float)rand() / RAND_MAX) * 1000;
    }
}

void UpdateAndDrawStars( SDL_Renderer *renderer, star stars[])
{
    // Loop through each star
    for ( int i = 0; i < NUMBER_OF_STARS; i++)
    {
        // Update the x-coordinate of the star based on its velocity
        stars[i].position.x -= (int)stars[i].velocity;

        // Wrap around stars that go off screen on the left side
        if (stars[i].position.x < 0)
        {
            // Reset the x-coordinate to the right edge of the window
            stars[i].position.x = WINDOW_WIDTH;

            // Randomly set the y-coordinate within the window height
            stars[i].position.y = rand() % WINDOW_HEIGHT;

            // Randomize the velocity for a new movement pattern
            stars[i].velocity = ((float)rand() / RAND_MAX) * 5 + 1;
        }

        // Calculate the size of the star based on its depth
        int size = 1 + (int)(stars[i].depth / 100);

        // Calculate the alpha value (transparency) based on the depth
        int alpha = (int)(255 - stars[i].depth / 10);

        // Set the render draw color to the calculated alpha for a fading effect
        SDL_SetRenderDrawColor( renderer, alpha, alpha, alpha, 255);
        
        // Render a single point (pixel) representing the star on the screen
        SDL_RenderDrawPoint( renderer, stars[i].position.x, stars[i].position.y);
    }

    // Introduce a small delay to control the frame rate of the animation
    SDL_Delay(10);
}

void CreateApple(fruit *apple)
{
    // Seed the random number generator with the current time
    srand(time(NULL));

    bool onSnake;

    // Generation of a random position of the apple within the window
    do
    {
        apple->position.x = (rand() % (WINDOW_WIDTH / SNAKE_SIZE)) * SNAKE_SIZE;
        apple->position.y = (rand() % (WINDOW_HEIGHT / SNAKE_SIZE)) * SNAKE_SIZE;

        onSnake = false;
        if (isHovering == onMode1)
        {
            // Checking if the apple is generated on the body of the snake in the first mode
            for ( int i = 0; i < snake.size && !onSnake; i++)
                onSnake = (snake.chunk[i].position.x == apple->position.x) && (snake.chunk[i].position.y == apple->position.y);
        }
        else if (isHovering == onMode2)
        {
            // Checking if the apple is generated on the body of the first snake in the second mode
            for (int i = 0; i < snake1.size && !onSnake; i++)
                onSnake = (snake1.chunk[i].position.x == apple->position.x) && (snake1.chunk[i].position.y == apple->position.y);

            if (!onSnake)
            {
                // Checking if the apple is generated on the body of the second snake in the second mode
                for (int i = 0; i < snake2.size && !onSnake; i++)
                    onSnake = (snake2.chunk[i].position.x == apple->position.x) && (snake2.chunk[i].position.y == apple->position.y);
            }
        }

    } while (((apple->position.x >= 750 && apple->position.x < 790) && (apple->position.y >= 0 && apple->position.y < 40) && (isHovering == onMode1)) ||
             (((apple->position.x >= 360 && apple->position.x < 440) && (apple->position.y >= 0 && apple->position.y < 40) || (apple->position.x >= 360 && apple->position.x < 440) && (apple->position.y >= 460 && apple->position.y < 500)) && (isHovering == onMode2)) ||
             onSnake);
}

void DrawApple(SDL_Renderer *renderer)
{
    // Rendering an image that is representing the apple
    SDL_Rect AppleCell = { apple.position.x, apple.position.y, SNAKE_SIZE, SNAKE_SIZE};
    SDL_RenderCopy( renderer, AppleTexture, NULL, &AppleCell);
}

void InitializeHighestScore(player *snake) { snake->highestScore = -1; }

void CreateSnake( player *snake, int initialX, int initialY)
{
    // Setting the snake to its initial parameters
    snake->size = SNAKE_INITIAL_SIZE, snake->score = 0, snake->highestScore = (snake->highestScore == -1)? 0: snake->highestScore, snake->state = true, snake->speed = 100;

    // Setting each chunk to its position
    for ( int i = 0; i < snake->size; i++)
    {
        snake->chunk[i].position.x = initialX - i * SNAKE_SIZE;
        snake->chunk[i].position.y = initialY;
        snake->chunk[i].angle = 0;
        snake->chunk[i].direction = STABLE;
    }
}

void DrawSnake( player *snake, SDL_Renderer *renderer, SnakeColor color)
{
    SDL_Texture *head, *body, *corner, *tail;

    if (color == GREEN)
    {
        head = GreenSnakeHeadTexture;
        body = GreenSnakeBodyTexture;
        corner = GreenSnakeCornerTexture;
        tail = GreenSnakeTailTexture;
    }
    else if (color == BLUE)
    {
        head = BlueSnakeHeadTexture;
        body = BlueSnakeBodyTexture;
        corner = BlueSnakeCornerTexture;
        tail = BlueSnakeTailTexture;
    }

    for ( int i = 0; i < snake->size; i++)
    {
        SDL_Rect SnakeSegment = { snake->chunk[i].position.x, snake->chunk[i].position.y, SNAKE_SIZE, SNAKE_SIZE};
        int previousDirection = snake->chunk[i+1].direction, currentDirection = snake->chunk[i].direction;

        if (i == 0) // Render snake head
            SDL_RenderCopyEx( renderer, head, NULL, &SnakeSegment, snake->chunk[i].angle, NULL, SDL_FLIP_NONE);
        else if (i == snake->size-1) // Render snake tail
            SDL_RenderCopyEx( renderer, tail, NULL, &SnakeSegment, snake->chunk[i].angle, NULL, SDL_FLIP_NONE);
        else if ((previousDirection == UP && currentDirection == RIGHT) || (previousDirection == LEFT && currentDirection == DOWN)) // Render snake corner
            SDL_RenderCopyEx( renderer, corner, NULL, &SnakeSegment, 0, NULL, SDL_FLIP_NONE);
        else if ((previousDirection == RIGHT && currentDirection == DOWN) || (previousDirection == UP && currentDirection == LEFT)) // Render snake corner
            SDL_RenderCopyEx( renderer, corner, NULL, &SnakeSegment, 90, NULL, SDL_FLIP_NONE);
        else if ((previousDirection == DOWN && currentDirection == LEFT) || (previousDirection == RIGHT && currentDirection == UP)) // Render snake corner
            SDL_RenderCopyEx( renderer, corner, NULL, &SnakeSegment, 180, NULL, SDL_FLIP_NONE);
        else if ((previousDirection == LEFT && currentDirection == UP) || (previousDirection == DOWN && currentDirection == RIGHT)) // Render snake corner
            SDL_RenderCopyEx( renderer, corner, NULL, &SnakeSegment, -90, NULL, SDL_FLIP_NONE);
        else // Render snake body
            SDL_RenderCopyEx( renderer, body, NULL, &SnakeSegment, snake->chunk[i].angle, NULL, SDL_FLIP_NONE);
    }
}

void MoveSnake(player *snake)
{
    // Check if the snake's head collides with its body
    for ( int i = 1; i < snake->size && isHovering == onMode1; i++)
    {
        if (snake->chunk[0].position.x == snake->chunk[i].position.x && snake->chunk[0].position.y == snake->chunk[i].position.y && snake->score != 0)
        {
            if (snake->score > snake->highestScore) snake->highestScore = snake->score;
            snake->state = false; // Snake collides with itself, game over
            MenuOption = GAMEOVER1;
            Mix_PlayMusic( GameOverMusic, 0);
            break;
        }
    }

    // Adjust snake position if it moves beyond the window boundaries
    if (snake->chunk[0].position.y < 0)
        snake->chunk[0].position.y = WINDOW_HEIGHT - SNAKE_SIZE;
    else if (snake->chunk[0].position.x < 0)
        snake->chunk[0].position.x = WINDOW_WIDTH - SNAKE_SIZE;
    else if (snake->chunk[0].position.y >= WINDOW_HEIGHT)
        snake->chunk[0].position.y = 0;
    else if (snake->chunk[0].position.x >= WINDOW_WIDTH)
        snake->chunk[0].position.x = 0;

    // Generating another position of the apple, increasing the size of the snake and playing a sound if the apple has been eaten by the snake 
    if (snake->chunk[0].position.x == apple.position.x && snake->chunk[0].position.y == apple.position.y)
    {
        Mix_PlayChannel( -1, EatingMusic, 0);
        snake->size++, snake->score++, snake->speed = (snake->speed > 50)? snake->speed -= 4: snake->speed;
        CreateApple(&apple);
    }

    // Shift the positions of snake chunks to follow the head
    for ( int i = snake->size-1; i > 0 && snake->chunk[0].direction != STABLE; i--)
        snake->chunk[i] = snake->chunk[i-1]; // Assign the position of the previous chunk to the current chunk

    // Switch statement to handle snake movement based on its direction
    switch (snake->chunk[0].direction)
    {
        case STABLE:
            break;
        case UP:
            snake->chunk[0].position.y -= SNAKE_SIZE;
            break;
        case RIGHT:
            snake->chunk[0].position.x += SNAKE_SIZE;
            break;
        case DOWN:
            snake->chunk[0].position.y += SNAKE_SIZE;
            break;
        case LEFT:
            snake->chunk[0].position.x -= SNAKE_SIZE;
            break;
    }
}

void DrawScore( player *snake, SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, SDL_Rect rect)
{
    // Defining an array characters to store the score as a string
    char ScoreString[50];

    // Convert the integer score to a string using itoa
    itoa(snake->score, ScoreString, 10);

    // Render the score string onto a surface using the provided font and color
    SDL_Surface *surface = TTF_RenderText_Solid( font, ScoreString, color);

    // Checking if the text was successfully rendered
    if (!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create a texture from the rendered surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, surface);

    // Checking if the texture was successfully created
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(surface);

    // Rendering the texture onto the renderer at a specific position and size
    SDL_RenderCopy( renderer, texture, NULL, &rect);
}

void RenderCountdown( SDL_Renderer *renderer, const char *text, SDL_Color color, SDL_Rect rect)
{
    // Render the text onto a surface using the provided font and color
    SDL_Surface *surface = TTF_RenderText_Solid(font28, text, color);

    // Checking if the text was successfully rendered
    if (!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        QuitSDL();
    }

    // Create a texture from the rendered surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Checking if the texture was successfully created
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        QuitSDL();
    }

    // Free the surface after creating the texture
    SDL_FreeSurface(surface);

    // Rendering the texture onto the renderer at a specific position and size
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    // Destroy the texture
    SDL_DestroyTexture(texture);
}