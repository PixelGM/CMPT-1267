#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

#include <string>
#include <fstream>
#include <iostream>	

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
	void RenderText(int, int, int);
	void saveText(int number, const std::string& filename);
	int loadText(const std::string& filename);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	int score = 0;
	int highestScore = 0;
	TTF_Font* mFont;
	SDL_Texture* mBallTexture = nullptr;
	SDL_Texture* mPaddleTexture = nullptr;
	SDL_Surface* paddleSurface;
	SDL_Texture* paddleTexture;
	SDL_Surface* ballSurface;
	SDL_Texture* ballTexture;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	
	bool mIsRunning;
	int mPaddleDir;
	Vector2 mPaddlePos;
	Vector2 mBallPos;
	Vector2 mBallVel;
};