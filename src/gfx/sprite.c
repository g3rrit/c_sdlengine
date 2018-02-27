//hdr
#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"

struct sprite
{
    int x;
    int y;
    int w;
    int h;
    double angle;

    SDL_Texture *tex;    
};

int sprite_init(struct sprite *this, char *path);

void sprite_set_dim(struct sprite *this, int x, int y, int w, int h, int angle);

void sprite_draw(struct sprite *this);

void sprite_delete(struct sprite *this);

//graphics
void gfx_draw_texture(SDL_Texture *tex, int x, int y, int w, int h, double angle);

SDL_Texture *gfx_load_texture(char *path);

#endif

//src
#ifndef SPRITE_C

#include "mstd.h"

int sprite_init(struct sprite *this, char *path)
{
    this->x = 0;
    this->y = 0;
    this->w = 30;
    this->h = 30;
    this->angle = 0;

    this->tex = gfx_load_texture(path);
}

void sprite_set_dim(struct sprite *this, int x, int y, int w, int h, int angle)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->angle = angle;
}

void sprite_draw(struct sprite *this)
{
    gfx_draw_texture(this->tex, this->x, this->y, this->w, this->h, this->angle);
}

void sprite_delete(struct sprite *this)
{
    SDL_DestroyTexture(this->tex);
}


//graphics
void gfx_draw_texture(SDL_Texture *tex, int x, int y, int w, int h, double angle)
{
    SDL_Rect temp_rect;
    temp_rect.x = x;
    temp_rect.y = y;
    temp_rect.w = w;
    temp_rect.h = h;
    if(angle == 0)
        SDL_RenderCopy(game_container.renderer, tex, 0, &temp_rect);
    else
        SDL_RenderCopyEx(game_container.renderer, tex, 0, &temp_rect, angle, 0, 0);
}

SDL_Texture *gfx_load_texture(char *path)
{
    SDL_Surface *surface = IMG_Load(path);
    if(surface == 0)
        printf("couldnt load img: %s\n", path);

    SDL_Texture *res_tex = SDL_CreateTextureFromSurface(game_container.renderer, surface);
    SDL_FreeSurface(surface);

    if(res_tex == 0)
        printf("couldnt create texutre\n");

    return res_tex;
}

#endif

