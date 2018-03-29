//hdr
#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "SDL_ttf.h"

TTF_Font *FONT_DEFAULT;

struct
{
} font_manager;

void font_manager_init();

void font_manager_delete();

#endif

//src
#ifndef FONTMANAGER_C

#include "mstd.h"

#define FONT_DIR "res/font/BitFont.ttf"

void font_manager_init()
{
    TTF_Init();
    FONT_DEFAULT = TTF_OpenFont(FONT_DIR,30);

    if(!FONT_DEFAULT)
        printf("error loading font: [default]\nERROR: %s\n", TTF_GetError());
}

void font_manager_delete()
{
    TTF_CloseFont(FONT_DEFAULT);
    TTF_Quit();
}

#endif
