#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

#include <iostream>
#include <cstdlib>

#include <Windows.h>

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	SDL_Texture* newTexture;
	SDL_Texture* newTexture2;
	SDL_Surface* textSurface;
	SDL_Surface* textSurface2;
	SDL_Color textColor;
	std::string textureText;
	std::string textureText2;
	TTF_Font* theFont;

	int mWidth;
	int mWidth2;
	int mHeight;
	int mHeight2;

	Uint32 mTicksCount;
	
	bool mIsRunning;
	int mPaddleDir;
	Vector2 mPaddlePos;
	Vector2 mBallPos;
	Vector2 mBallVel;
};
