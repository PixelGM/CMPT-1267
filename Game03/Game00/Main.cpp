#include "SDL/SDL.h"
#include <iostream>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char* args[])
{
	SDL_Window* myWindow = nullptr;
	SDL_Surface* myScreenSurface = nullptr;
	SDL_Surface* HelloSDLSurface = nullptr;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL Init failed: " << SDL_GetError() << endl;
	}
	else
	{
		myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, WIDTH, HEIGHT, 0);
		if (myWindow == nullptr)
		{
			cout << "Create Window failed: " << SDL_GetError() << endl;
		}
		else
		{
			myScreenSurface = SDL_GetWindowSurface(myWindow);
			HelloSDLSurface = SDL_LoadBMP("HelloSDL.bmp");
			if (HelloSDLSurface == nullptr)
			{
				cout << "Unable to load " << "HelloSDL.bmp" << SDL_GetError() << endl;
			}
			else
			{
				bool done = false;
				SDL_Event event;

				while (!done)
				{
					while (SDL_PollEvent(&event) != 0)
					{
						if (event.type == SDL_QUIT) // SDL_QUIT is when user press 'X' or Alt + F4
						{
							done = true;
						}
						else if (event.type == SDL_KEYDOWN)
						{
							if (event.key.keysym.sym == SDLK_0) // Press '0' to end the image
							{
								done = true;
							}
						}
					}

					SDL_BlitSurface(HelloSDLSurface, NULL, myScreenSurface, NULL);
					SDL_UpdateWindowSurface(myWindow);
					//SDL_Delay(5000);
				}
			}
		}
	}

	SDL_FreeSurface(HelloSDLSurface);
	HelloSDLSurface = nullptr;
	SDL_FreeSurface(myScreenSurface);
	myScreenSurface = nullptr;
	SDL_DestroyWindow(myWindow);
	myWindow = nullptr;
	SDL_Quit();
	return 0;
}