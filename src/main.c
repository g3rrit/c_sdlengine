#include "SDL.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    SDL_Window *window = 0;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
            "window",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_OPENGL
    );

    if(!window)
    {
        printf("couldnt createe window %s\n", SDL_GetError());
        return 1;
    }

    SDL_Delay(3000);

    SDL_Quit();

    return 0;
}
