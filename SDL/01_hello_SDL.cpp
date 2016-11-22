/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <string>

#include "ltexture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gFooTexture;
LTexture gBackgroundTexture;


//Loads individual image as texture
SDL_Texture* loadTexture( std::string path ) {
    //The final texture
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else {
        //Create texture
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Free surface
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}


//Starts up SDL and creates window
bool init() {
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL, SDL_Error; %s\n", SDL_GetError());
        success = false;
    }
    else {
        //Create Window
        gWindow = SDL_CreateWindow("XD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Unable to create window! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

//Loads media
bool loadMedia() {
    bool success = true;

    //Load Foo texture
    if (!gFooTexture.loadFromFile("../images/foo.png", gRenderer)) {
        printf("Failed to load Foo texture image! \n");
        success = false;
    }

    //Load background texture
    if (!gBackgroundTexture.loadFromFile("../images/background.png", gRenderer)) {
        printf("Failed to load background texture image! \n");
        success = false;
    }

    return success;
}

//Frees media and shuts down SDL
void close() {
    //Free loaded images
    gFooTexture.free();
    gBackgroundTexture.free();

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    //Quit SDL
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    if (!init()) {
        printf("Failed to initialize!\n");
    }
    else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        }
        else {

            bool quit = false;

            //Event handler
            SDL_Event e;

            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                //Render background
                gBackgroundTexture.render(gRenderer, 0, 0);

                //Render foo
                gFooTexture.render(gRenderer, 240, 190);

                //Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    close();

	return 0;
}
