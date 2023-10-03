#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <iostream>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	SDL_Window* myWindow = nullptr;
	SDL_Texture* newTexture = nullptr;
	SDL_Renderer* theRenderer = nullptr;
	TTF_Font* theFont = nullptr;
	int mWidth;
	int mHeight;

	SDL_Init(SDL_INIT_VIDEO);
	myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	TTF_Init();

	theFont = TTF_OpenFont("Dubai-Regular.ttf", 28);
	if (theFont == nullptr)
	{
		cout << "Failed to open font\n";
	}
	else
	{
		SDL_Color textColor = { 0, 0, 0 };
		string textureText = "Welcome to the Hotel California, such a lovely place!";

		SDL_Surface* textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), textColor);
		newTexture = SDL_CreateTextureFromSurface(theRenderer, textSurface);

		mWidth = textSurface->w;
		mHeight = textSurface->h;

		SDL_FreeSurface(textSurface);

		bool Done = false;
		double angle = 45;

		SDL_Event e;
		while (!Done)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					Done = true;
				}
				else if (e.type == SDL_KEYDOWN) // Check for key press
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_UP: // Check if the key is the up arrow
						angle += 45;
						break;
					case SDLK_DOWN: // Check if the key is the up arrow
						angle -= 45;
						break;
					default:
						break;
					}
				}
			}

			SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(theRenderer);

			int x = (SCREEN_WIDTH - mWidth) / 2;
			int y = (SCREEN_HEIGHT - mHeight) / 2;
			SDL_Rect* clip = nullptr;

			SDL_Rect renderQuad = { x, y, mWidth, mHeight };
			if (clip != nullptr)
			{
				renderQuad.w = clip->w;
				renderQuad.h = clip->h;
			}
			SDL_RenderCopyEx(theRenderer, newTexture, clip, &renderQuad, angle, NULL, SDL_FLIP_NONE);
			SDL_RenderPresent(theRenderer);
		}

	}

	TTF_CloseFont(theFont);
	SDL_DestroyTexture(newTexture);
	newTexture = nullptr;
	SDL_DestroyRenderer(theRenderer);
	theRenderer = nullptr;
	SDL_DestroyWindow(myWindow);
	myWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
	return 0;
}