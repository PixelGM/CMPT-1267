#include "SDL/SDL.h"
#include <iostream>
#include <string>
#include <SDL/SDL_ttf.h>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
	SDL_Window* myWindow = NULL;
	SDL_Renderer* theRenderer = NULL;
	SDL_Texture* newTexture = NULL;
	TTF_Font* theFont = NULL;
	int mWidth;
	int mHeight;

	SDL_Init(SDL_INIT_VIDEO);
	myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);

	TTF_Init();

	theFont = TTF_OpenFont("Dubai-Regular.ttf", 28);
	string textureText = "O";
	SDL_Color textColor = { 0, 0, 255 };

	

	

	bool Done = false;
	bool onee = false;
	bool twoo = false;
	bool threee = false;
	bool fourr = false;

	SDL_Event e;
	while (!Done)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				Done = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_1:
					onee = true;
					twoo = false;
					threee = false;
					fourr = false;
					break;

				case SDLK_2:
					onee = false;
					twoo = true;
					threee = false;
					fourr = false;
					break;

				case SDLK_3:
					onee = false;
					twoo = false;
					threee = true;
					fourr = false;
					break;

				case SDLK_4:
					onee = false;
					twoo = false;
					threee = false;
					fourr = true;
					break;
				default:
					onee = false;
					twoo = false;
					threee = false;
					fourr = false;
					break;
				}
			}
		}
		SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(theRenderer);

		// SDL_Rect fillRect = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }; // This is Bottom Left
		SDL_Rect fillRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_SetRenderDrawColor(theRenderer, 0, 255, 0, 255);
		SDL_RenderFillRect(theRenderer, &fillRect);

		// Render One
		if (onee == true)
		{
			SDL_Surface* textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), textColor);
			newTexture = SDL_CreateTextureFromSurface(theRenderer, textSurface);

			mWidth = textSurface->w;
			mHeight = textSurface->h;

			SDL_FreeSurface(textSurface);

			int x = (SCREEN_WIDTH - mWidth) / 4;
			int y = (SCREEN_HEIGHT - mHeight) / 4;

	
			textureText = "One";
			
			double angle = 0;
			SDL_Rect renderQuad = { x, y, mWidth, mHeight };

			// Vectical and Horizontal Line
			SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
			SDL_RenderDrawLine(theRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
			SDL_RenderDrawLine(theRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);

			SDL_RenderCopyEx(theRenderer, newTexture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
			SDL_RenderPresent(theRenderer);
		}
		else if (twoo == true)
		{
			SDL_Surface* textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), textColor);
			newTexture = SDL_CreateTextureFromSurface(theRenderer, textSurface);

			mWidth = textSurface->w;
			mHeight = textSurface->h;

			SDL_FreeSurface(textSurface);

			int x = (SCREEN_WIDTH + mWidth) - 200;
			int y = (SCREEN_HEIGHT - mHeight) / 4;


			textureText = "Two";

			double angle = 0;
			SDL_Rect renderQuad = { x, y, mWidth, mHeight };

			// Vectical and Horizontal Line
			SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
			SDL_RenderDrawLine(theRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
			SDL_RenderDrawLine(theRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);

			SDL_RenderCopyEx(theRenderer, newTexture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
			SDL_RenderPresent(theRenderer);
		}
		else if (threee == true)
		{
			SDL_Surface* textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), textColor);
			newTexture = SDL_CreateTextureFromSurface(theRenderer, textSurface);

			mWidth = textSurface->w;
			mHeight = textSurface->h;

			SDL_FreeSurface(textSurface);

			int x = (SCREEN_WIDTH - mWidth) / 4 ;
			int y = (SCREEN_HEIGHT - mHeight) / 4 + ((SCREEN_WIDTH - mWidth) / 2);


			textureText = "Three";

			double angle = 0;
			SDL_Rect renderQuad = { x, y, mWidth, mHeight };

			// Vectical and Horizontal Line
			SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
			SDL_RenderDrawLine(theRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
			SDL_RenderDrawLine(theRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);

			SDL_RenderCopyEx(theRenderer, newTexture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
			SDL_RenderPresent(theRenderer);
		}
		else if (fourr == true)
		{
			SDL_Surface* textSurface = TTF_RenderText_Solid(theFont, textureText.c_str(), textColor);
			newTexture = SDL_CreateTextureFromSurface(theRenderer, textSurface);

			mWidth = textSurface->w;
			mHeight = textSurface->h;

			SDL_FreeSurface(textSurface);

			int x = (SCREEN_WIDTH + mWidth) - 200;
			int y = (SCREEN_HEIGHT - mHeight) - 100;


			textureText = "Four";

			double angle = 0;
			SDL_Rect renderQuad = { x, y, mWidth, mHeight };

			// Vectical and Horizontal Line
			SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
			SDL_RenderDrawLine(theRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
			SDL_RenderDrawLine(theRenderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);

			SDL_RenderCopyEx(theRenderer, newTexture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE);
			SDL_RenderPresent(theRenderer);
		}


		/*SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
		SDL_SetRenderDrawColor(theRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(theRenderer, &outlineRect);*/

		


		//SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);

		/*for (int i = 0; i < SCREEN_HEIGHT; i += 4)
		{
			SDL_RenderDrawPoint(theRenderer, SCREEN_WIDTH / 2, i);
		}*/
		SDL_RenderPresent(theRenderer);
	}

	SDL_DestroyRenderer(theRenderer);
	SDL_DestroyWindow(myWindow);

	SDL_Quit();
	return 0;
}