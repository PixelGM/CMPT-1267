#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

int changeColorR = 0;
int changeColorG = 255;
int changeColorB = 0;

const std::string FILENAME = "file.txt";
char scoreChar;

Mix_Chunk* collisionSound = nullptr;
Mix_Music* backgroundMusic = nullptr;

Game::Game()
{	
	mWindow=nullptr;
	mRenderer=nullptr;
	mTicksCount=0;
	mIsRunning=true;
	mPaddleDir=0;
}

void Game::RenderText(int number, int x, int y)
{
	char buffer[50];
	sprintf(buffer, "%d", number);  // Convert int to char array

	SDL_Color color = { 255, 255, 255 };  // White
	SDL_Surface* surface = TTF_RenderText_Solid(mFont, buffer, color);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FreeSurface(surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);

	SDL_Rect dstRect = { x, y, texW, texH };
	SDL_RenderCopy(mRenderer, texture, NULL, &dstRect);

	SDL_DestroyTexture(texture);
}

void Game::saveText(int number, const std::string& filename)
{
	std::ofstream outFile(filename);
	if (outFile.is_open())
	{
		outFile << number;
		outFile.close();
	}
	else
	{
		std::cerr << "Unable to open file for writing: " << filename << std::endl;
	}
}

int Game::loadText(const std::string& filename)
{
	int number = 0;
	std::ifstream inFile(filename);
	if (inFile.is_open())
	{
		inFile >> number;
		inFile.close();
	}
	else
	{
		std::cerr << "Unable to open file for reading: " << filename << std::endl;
	}
	return number;
}

bool Game::Initialize()
{
	highestScore = loadText(FILENAME);
	
	
	//setPaddleTexture("path/to/paddle.jpg");

	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
		return false;
	}

	// Load sound effects
	collisionSound = Mix_LoadWAV("collision.wav");
	if (collisionSound == nullptr)
	{
		SDL_Log("Failed to load collision sound effect! SDL_mixer Error: %s", Mix_GetError());
		return false;
	}

	// Load music
	backgroundMusic = Mix_LoadMUS("soundtrack.wav");
	if (backgroundMusic == nullptr)
	{
		SDL_Log("Failed to load background music! SDL_mixer Error: %s", Mix_GetError());
		return false;
	}

	// Play the music
	Mix_PlayMusic(backgroundMusic, -1);

	// TTF Error Handling
	if (TTF_Init() == -1)
	{
		SDL_Log("Failed to initialize TTF: %s", TTF_GetError());
		return false;
	}

	mFont = TTF_OpenFont("futur.ttf", 24);  // Replace with actual path and size

	if (!mFont)
	{
		SDL_Log("Failed to load font: %s", TTF_GetError());
		return false;
	}


	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"CMPT 1267", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1024,	// Width of window
		768,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f/2.0f;
	mBallPos.x = 1024.0f/2.0f;
	mBallPos.y = 768.0f/2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

	// Load paddle texture
	paddleSurface = IMG_Load("paddle.png");
	if (!paddleSurface)
	{
		SDL_Log("Failed to load image: %s", IMG_GetError());
		return false;
	}
	paddleTexture = SDL_CreateTextureFromSurface(mRenderer, paddleSurface);
	SDL_FreeSurface(paddleSurface);  // Free the temporary surface
	// Load ball texture
	ballSurface = IMG_Load("ball.png");
	if (!ballSurface)
	{
		SDL_Log("Failed to load image: %s", IMG_GetError());
		return false;
	}
	ballTexture = SDL_CreateTextureFromSurface(mRenderer, ballSurface);
	SDL_FreeSurface(ballSurface);  // Free the temporary surface

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				TTF_CloseFont(mFont);
				TTF_Quit();
				saveText(highestScore, FILENAME);
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_z)
				{
					if (Mix_PausedMusic() == 1)
					{
						Mix_ResumeMusic();
					}
					else
					{
						Mix_PauseMusic();
					}
				}
				break;

				

		}
	}
	
	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	
	// Update paddle direction based on W/S keys
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	
	// Update paddle position based on direction
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen!
		if (mPaddlePos.y < (paddleH/2.0f + thickness))
		{
			mPaddlePos.y = paddleH/2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH/2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH/2.0f - thickness;
		}
	}
	
	// Update ball position based on ball velocity
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;
	
	// Bounce if needed
	// Did we intersect with the paddle?
	float diff = mPaddlePos.y - mBallPos.y;
	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= paddleH / 2.0f &&
		// We are in the correct x-position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		// The ball is moving to the left
		mBallVel.x < 0.0f)
	{
		// If ball collide paddle HEREHERE
		mBallVel.x *= -1.0f;
		
		// Play collision sound
		Mix_PlayChannel(-1, collisionSound, 0);

		if (changeColorG == 255)
		{
			changeColorG = 0;
			changeColorR = 255;
		} 
		else
		{
			changeColorG = 255;
			changeColorR = 0;
		}
		// Increase Score
		score++;

		if (highestScore <= score)
		{
			highestScore = score;
		}

		
		
	}
	// Did the ball go off the screen? (if so, end game)
	else if (mBallPos.x <= 0.0f)
	{
		saveText(highestScore, FILENAME);
		mIsRunning = false;
	}
	// Did the ball collide with the right wall?
	else if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}
	
	// Did the ball collide with the top wall?
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (mBallPos.y >= (768 - thickness) &&
		mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}
}

void Game::GenerateOutput()
{
	// Set draw color to blue (BACKROUND)
	SDL_SetRenderDrawColor(
		mRenderer,
		changeColorR,		// R
		changeColorG,		// G 
		changeColorB,	// B
		255		// A
	);
	
	// Clear back buffer (REFRESH SCREEN)
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 0, 255);
	
	// Draw top wall
	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		1024,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);
	
	// Draw right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	
	// Draw paddle using texture
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderCopy(mRenderer, paddleTexture, NULL, &paddle);

	// Draw ball using texture
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderCopy(mRenderer, ballTexture, NULL, &ball);
	
	// Draw Text
	RenderText(score, 500, 500);
	RenderText(highestScore, 500, 600);
	

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	// Free sound effects and music	
	Mix_FreeChunk(collisionSound);
	Mix_FreeMusic(backgroundMusic);

	SDL_DestroyTexture(paddleTexture);
	SDL_DestroyTexture(ballTexture);

	// Quit SDL_mixer
	Mix_Quit();
	SDL_Quit();
}