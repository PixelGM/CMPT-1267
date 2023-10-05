#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
    SDL_Window* myWindow = NULL;
    SDL_Texture* texture1 = NULL;
    SDL_Texture* texture2 = NULL;
    SDL_Renderer* theRenderer = NULL;

    int textureWidth;
    int textureHeight;

    SDL_Init(SDL_INIT_VIDEO);
    myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    IMG_Init(IMG_INIT_PNG);

    string imageFile1 = "arrow.png";
    string imageFile2 = "arrow2.png";
    SDL_Surface* surface1 = IMG_Load(imageFile1.c_str());
    texture1 = SDL_CreateTextureFromSurface(theRenderer, surface1);
    SDL_Surface* surface2 = IMG_Load(imageFile2.c_str());
    texture2 = SDL_CreateTextureFromSurface(theRenderer, surface2);

    textureWidth = surface1->w;
    textureHeight = surface1->h;

    SDL_FreeSurface(surface1);
    SDL_FreeSurface(surface2);

    bool Done = false;
    SDL_Event e;
    double degrees = 0;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;
    bool useTexture1 = true; // flag to switch between textures
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
                case SDLK_a:
                    degrees -= 60;
                    break;

                case SDLK_s:
                    degrees += 60;
                    break;

                case SDLK_q:
                    flipType = SDL_FLIP_HORIZONTAL;
                    break;

                case SDLK_w:
                    flipType = SDL_FLIP_NONE;
                    break;

                case SDLK_e:
                    flipType = SDL_FLIP_VERTICAL;
                    break;

                case SDLK_m:
                    useTexture1 = true; // switch to texture1
                    break;

                case SDLK_n:
                    useTexture1 = false; // switch to texture2
                    break;
                }
            }
        }

        //Clear screen
        SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(theRenderer);

        //Render arrow
        int x = (SCREEN_WIDTH - textureWidth) / 2;
        int y = (SCREEN_HEIGHT - textureHeight) / 2;
        SDL_Rect* clip = NULL;
        SDL_Rect renderQuad = { x, y, textureWidth, textureHeight };
        //Set clip rendering dimensions
        if (clip != NULL)
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }
        //Render to screen
        if (useTexture1) {
            SDL_RenderCopyEx(theRenderer, texture1, clip, &renderQuad, degrees, NULL, flipType);
        }
        else {
            SDL_RenderCopyEx(theRenderer, texture2, clip, &renderQuad, degrees, NULL, flipType);
        }

        //Update screen
        SDL_RenderPresent(theRenderer);
    }

    // Free memory
    SDL_DestroyTexture(texture1);
    texture1 = NULL;

    SDL_DestroyTexture(texture2);
    texture2 = NULL;

    SDL_DestroyRenderer(theRenderer);
    theRenderer = NULL;

    IMG_Quit();
    SDL_Quit();

    return 0;
}
