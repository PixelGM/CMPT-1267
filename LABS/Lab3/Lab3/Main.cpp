#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void drawCircle(SDL_Renderer* renderer, int cx, int cy, int radius, bool filled)
{
	if (filled)
	{
		for (double dy = 1; dy <= radius; dy += 1.0)
		{
			double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
			SDL_RenderDrawLine(renderer, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
			SDL_RenderDrawLine(renderer, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
		}
	}
	else
	{
		for (double i = 0; i < 360; i += 1.0)
		{
			double angle = i * M_PI / 180;
			int x = (int)(cx + radius * cos(angle));
			int y = (int)(cy + radius * sin(angle));
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
}


int main(int argc, char* args[])
{
	SDL_Window* myWindow = NULL;
	SDL_Texture* newTexture = NULL;
	SDL_Renderer* theRenderer = NULL;

	SDL_Init(SDL_INIT_VIDEO);
	myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	IMG_Init(IMG_INIT_PNG);

	bool Done = false;
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
		SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(theRenderer);

		// Define the circle's center and radius
		int cx = SCREEN_WIDTH / 2;
		int cy = SCREEN_HEIGHT / 2;
		int radius = std::min(SCREEN_WIDTH, SCREEN_HEIGHT) / 4;

		// Set the render color (red in this case)
		SDL_SetRenderDrawColor(theRenderer, 0xFF, 0x00, 0x00, 0xFF);

		// Call the drawCircle function
		drawCircle(theRenderer, cx, cy, radius, true);


		SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
		SDL_SetRenderDrawColor(theRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(theRenderer, &outlineRect);


		SDL_SetRenderDrawColor(theRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderDrawLine(theRenderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);


		SDL_SetRenderDrawColor(theRenderer, 0x00, 0x00, 0x00, 0xFF);
		for (int i = 0; i < SCREEN_HEIGHT; i += 4)
		{
			SDL_RenderDrawPoint(theRenderer, SCREEN_WIDTH / 2, i);
		}
		SDL_RenderPresent(theRenderer);
	}

	SDL_DestroyTexture(newTexture);
	newTexture = NULL;

	SDL_DestroyRenderer(theRenderer);
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;
	theRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
	return 0;
}