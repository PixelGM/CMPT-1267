#include "SDL/SDL.h"
#include <iostream>
using namespace std;

int main(int argc, char* args[])
{
	SDL_Window* myWindow = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Surface* HelloSDLSurface = nullptr;
	SDL_Surface* array[5];
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "Initialization failed!" << endl;
	else
	{
		myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, 800, 600, 0);
		if (myWindow == nullptr)
			cout << "Window was not created!" << endl;
		else
		{
			screenSurface = SDL_GetWindowSurface(myWindow);
			//HelloSDLSurface = SDL_LoadBMP("HelloSDL.bmp");
			/*if (HelloSDLSurface == nullptr)
				cout << "Unable to load HelloSDL.bmp\n";
			else
			{*/
				bool Done = false;
				SDL_Event eve;

				// Cache to memory
				array[0] = SDL_LoadBMP("default.bmp");
				array[1] = SDL_LoadBMP("a.bmp");
				array[2] = SDL_LoadBMP("b.bmp");
				array[3] = SDL_LoadBMP("c.bmp");
				array[4] = SDL_LoadBMP("d.bmp");
				HelloSDLSurface = array[0];
				while (!Done)
				{
					while (SDL_PollEvent(&eve) != 0)
					{

						/*if (eve.type == SDL_QUIT)
						{
							Done = true;
						}
						else if (eve.type == SDL_KEYDOWN)
						{
							if (eve.key.keysym.sym == SDLK_0)
							{
								Done = true;
							}
						}*/

						if (eve.type == SDL_QUIT)
						{
							Done = true;
						}
						else if (eve.type == SDL_KEYDOWN || eve.type == SDL_KEYUP)
						//else if (true)
						{
							if (eve.key.keysym.sym)
							{
								switch (eve.key.keysym.sym)
								{
								case SDLK_a:
									HelloSDLSurface = array[1];
									break;
								case SDLK_b:
									HelloSDLSurface = array[2];
									break;
								case SDLK_c:
									HelloSDLSurface = array[3];
									break;
								case SDLK_d:
									HelloSDLSurface = array[4];
									break;
								default:
									HelloSDLSurface = array[0];
								}
							}
						}

					}

					SDL_BlitSurface(HelloSDLSurface, NULL, screenSurface, NULL);
					SDL_UpdateWindowSurface(myWindow);
				}
			//}
		}
	}
	SDL_FreeSurface(HelloSDLSurface);
	HelloSDLSurface = nullptr;
	SDL_FreeSurface(screenSurface);
	screenSurface = nullptr;
	SDL_DestroyWindow(myWindow);
	myWindow = nullptr;
	for (int i = 0; i < 5; i++)
	{
		SDL_FreeSurface(array[i]);
		array[i] = nullptr;
	}
	SDL_Quit();
	return 0;
}