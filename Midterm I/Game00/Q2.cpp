// QUESTION 2

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <iostream>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	SDL_Window* myWindow = NULL;
	SDL_Texture* newTexture = NULL;
	SDL_Texture* newTexture2 = NULL;
	SDL_Renderer* theRenderer = NULL;
	TTF_Font* theFont = NULL;
	int mWidth;
	int mWidth2;
	int mHeight;
	int mHeight2;


	SDL_Init(SDL_INIT_VIDEO);
	myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	TTF_Init();

	theFont = TTF_OpenFont("Dubai-Regular.ttf", 28);
	string textureText = "Welcome to Douglas College";
	string textureText2 = "SDL is Awesome";
	SDL_Color textColor = { 255, 255, 255 };

	SDL_Surface* textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), textColor);
	SDL_Surface* textSurface2 = TTF_RenderText_Solid(theFont, textureText2.c_str(), textColor);
	newTexture = SDL_CreateTextureFromSurface(theRenderer, textSurface);
	newTexture2 = SDL_CreateTextureFromSurface(theRenderer, textSurface2);

	mWidth = textSurface->w;
	mHeight = textSurface->h;
	mWidth2 = textSurface2->w;
	mHeight2 = textSurface2->h;
	double x1 = 0;
	double x2 = SCREEN_WIDTH - 300;
	double y1 = 0;
	double y2 = 0;

	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(textSurface2);

	bool Done = false;
	double angle = 45;
	double angle2 = 45;

	SDL_Event e;
	while (!Done)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				Done = true;
			}
		}
		SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(theRenderer);

		x1 += 0.01;
		y1 = 145;

		x2 -= 0.01;
		y2 = 500;

		angle += 0.01;
		angle2 -= 0.01;

		SDL_Rect renderQuad = { x1, y1, mWidth, mHeight };
		SDL_Rect renderQuad2 = { x2, y2, mWidth, mHeight };
		SDL_RenderCopyEx(theRenderer, newTexture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
		SDL_RenderCopyEx(theRenderer, newTexture2, NULL, &renderQuad2, angle2, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(theRenderer);
	}

	SDL_DestroyTexture(newTexture);
	SDL_DestroyTexture(newTexture2);
	SDL_DestroyRenderer(theRenderer);
	SDL_DestroyWindow(myWindow);
	SDL_Quit();
	return 0;
}