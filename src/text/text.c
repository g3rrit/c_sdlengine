//hdr
#ifndef TEXT_H
#define TEXT_H

#include "SDL.h"

struct text
{
    char *txt;
    int x;
    int y;
    int w;
    int h;

    SDL_Color color;

    SDL_Texture *tex;
};

void text_init(struct text *this, char *txt);

void text_update_text(struct text *this, char *txt);

void text_set_dim(struct text *this, int x, int y, int w, int h);

void text_set_color(struct text *this, char a, char r, char g, char b);

void text_draw(struct text *this);

void text_delete(struct text *this);

#endif

//src
#ifndef TEXT_C

#include "mstd.h"

#include "SDL_ttf.h"
#include "string.h"

#define FONTMANAGER_C
#include "fontmanager.c"
#undef FONTMANAGER_C

void text_init(struct text *this, char *txt)
{
    this->x = 0;
    this->y = 20;
    this->w = 5 * strlen(txt);
    this->h = 10;
    this->color.a = 255;
    this->color.r = 255;
    this->color.g = 255;
    this->color.b = 255;
    text_update_text(this, txt);
}


void text_update_text(struct text *this, char *txt)
{
    this->txt = malloc(sizeof(strlen(txt) + 1));
    strcpy(this->txt, txt);

    SDL_Surface *surface = TTF_RenderText_Solid(FONT_DEFAULT, this->txt, this->color);
    this->tex = SDL_CreateTextureFromSurface(game_container.renderer, surface);
    SDL_FreeSurface(surface);
}

void text_set_dim(struct text *this, int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void text_set_color(struct text *this, char a, char r, char g, char b)
{
    this->color.a = a;
    this->color.r = r;
    this->color.g = g;
    this->color.b = b;
}

void text_draw(struct text *this)
{
    SDL_Rect temp_rect;
    temp_rect.x = this->x;
    temp_rect.y = this->y;
    temp_rect.w = this->w;
    temp_rect.h = this->h;

    SDL_RenderCopy(game_container.renderer, this->tex, 0, &temp_rect);
}

void text_delete(struct text *this)
{
    if(this->tex)
        SDL_DestroyTexture(this->tex);

    if(this->txt)
        free(this->txt);
}

#endif
