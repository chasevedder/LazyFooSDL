#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class LTexture
{
public:
    LTexture();

    ~LTexture();

    //Loads image at path
    bool loadFromFile(std::string path, SDL_Renderer* renderer);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(SDL_Renderer* renderer, int x, int y);

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //Actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif
