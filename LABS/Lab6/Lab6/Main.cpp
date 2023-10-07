#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Texture* LoadTexture(const string& file, SDL_Renderer* ren) {
    SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str());
    if (texture == nullptr) {
        cerr << "Failed to load texture: " << SDL_GetError() << endl;
    }
    return texture;
}

int main(int argc, char* args[]) {
    SDL_Window* myWindow = NULL;
    SDL_Renderer* theRenderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    myWindow = SDL_CreateWindow("CMPT 1267", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    theRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* frontTexture = LoadTexture("1.png", theRenderer);
    SDL_Texture* backTexture = LoadTexture("2.png", theRenderer);
    SDL_Texture* sideTexture = LoadTexture("3.png", theRenderer);
    SDL_Texture* topTexture = LoadTexture("4.png", theRenderer);

    bool done = false;
    SDL_Event e;

    while (!done) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                done = true;
            }
        }

        SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(theRenderer);

        SDL_Rect viewports[4] = {
            {0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
            {SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
            {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
            {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
        };

        SDL_Texture* textures[4] = { frontTexture, backTexture, sideTexture, topTexture };

        for (int i = 0; i < 4; ++i) {
            SDL_RenderSetViewport(theRenderer, &viewports[i]);
            SDL_RenderCopy(theRenderer, textures[i], NULL, NULL);
        }

        SDL_RenderPresent(theRenderer);
    }

    SDL_DestroyTexture(frontTexture);
    SDL_DestroyTexture(backTexture);
    SDL_DestroyTexture(sideTexture);
    SDL_DestroyTexture(topTexture);

    SDL_DestroyRenderer(theRenderer);
    SDL_DestroyWindow(myWindow);

    IMG_Quit();
    SDL_Quit();

    return 0;
}