#include "SDL/SDL.h"
#include <iostream>
#include <Windows.h>

using namespace std;

const int width = 800;
const int height = 600;

int main(int argc, char* args[])
{
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL_Init Error bruh: " << SDL_GetError() << endl;
	}
	else
	{
		window = SDL_CreateWindow("CMPT 1267", 100, 100, width, height, 0);

		if (window == nullptr)
			cout << "Window Creaton Failed, Dayum" << SDL_GetError() << endl;
		else
		{
			screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 127, 127, 255));
			SDL_UpdateWindowSurface(window);
			//SDL_Delay(5000);
			SDL_Delay(10000000);
		}

		SDL_FreeSurface(screenSurface);
		screenSurface = nullptr;
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_Quit();

		return 0;
	}
}