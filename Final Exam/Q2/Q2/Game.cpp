
#include "Game.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Define all Variables
int R = 0;
int G = 0;
int B = 0;

bool isR = false;
bool isG = false;
bool isB = false;
bool isY = false;
bool isW = false;

bool aIsPresed = false;

int A = 255;
//int random = rand() % 100; // Random Number 0 to 99

void setRandomColor(int* r, int* g, int* b)
{
	srand(time(NULL));
	int random = rand() % 6; // Random Number 0 to 5

	// Set to Red
	if (random == 0)
	{
		*r = 255;
		*g = 0;
		*b = 0;
	}
	// Set to Green
	else if (random == 1)
	{
		*r = 0;
		*g = 255;
		*b = 0;
	}
	// Set to Blue
	else if (random == 3)
	{
		*r = 0;
		*g = 0;
		*b = 255;
	}
	// Set to White
	else if (random == 4)
	{
		*r = 255;
		*g = 255;
		*b = 255;
	}
	// Set to Yellow
	else if (random == 5)
	{
		*r = 255;
		*g = 255;
		*b = 0;
	}
	// Just in case if it's not 0-5 range, set it to White.
	else
	{
		*r = 255;
		*g = 255;
		*b = 255;
	}

	return;
}

Game::Game()
{
	mWindow=nullptr;
	mRenderer=nullptr;
	mTicksCount=0;
	mIsRunning=true;
}

bool Game::Initialize()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Final Exam Game Dev I Q2", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		SCREEN_WIDTH,	// Width of window
		SCREEN_HEIGHT,	// Height of window
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

	TTF_Init();
	theFont = TTF_OpenFont("Dubai-Regular.ttf", 28);
	textureText = "Remaining Time: ";
	textureText2 = "Best Score: ";

	SDL_Color textColor = { 0, 0, 0 };

	textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), textColor);
	textSurface2 = TTF_RenderText_Solid(theFont, textureText2.c_str(), textColor);
	newTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);
	newTexture2 = SDL_CreateTextureFromSurface(mRenderer, textSurface2);

	// Get Sreen Width and Height
	mWidth = textSurface->w;
	mHeight = textSurface->h;
	mWidth2 = textSurface2->w;
	mHeight2 = textSurface2->h;

	setRandomColor(&R, &G, &B);

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
		if (event.type == SDL_QUIT)
		{
			mIsRunning = false;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				Sleep(1000);
				textureText = "a";
				textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), textColor);
				newTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);

				mWidth = textSurface->w;
				mHeight = textSurface->h;

				aIsPresed = true;
				break;
			}
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
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

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
}

void Game::GenerateOutput()
{
	// Set draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		R,		// R
		G,		// G 
		B,		// B
		A		// A
	);

	
	
	// Clear back buffer
	SDL_RenderClear(mRenderer);

	// Draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	

	int x = (SCREEN_WIDTH - mWidth) / 2;
	int y = (SCREEN_HEIGHT - mHeight) / 2;
	double angle = 0;
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };


	int x2 = (SCREEN_WIDTH - mWidth) / 2 + 350;
	int y2 = (SCREEN_HEIGHT - mHeight) / 2 - 330;
	SDL_Rect renderQuad2 = { x2, y2, mWidth, mHeight };

	/*textureText = "C";
	textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), textColor);
	newTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);

	mWidth = textSurface->w;
	mHeight = textSurface->h;
	
	Sleep(500);

	textureText = "B";
	textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), textColor);
	newTexture = SDL_CreateTextureFromSurface(mRenderer, textSurface);

	mWidth = textSurface->w;
	mHeight = textSurface->h;

	Sleep(500);*/

	SDL_RenderCopyEx(mRenderer, newTexture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
	SDL_RenderCopyEx(mRenderer, newTexture2, NULL, &renderQuad2, angle, NULL, SDL_FLIP_NONE);

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}