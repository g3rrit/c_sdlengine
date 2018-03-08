//hdr
#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"

//---------- SPRITE ---------- 

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

void sprite_change_texture(struct sprite *this, char *path);

void sprite_draw(struct sprite *this);

void sprite_delete(struct sprite *this);

//---------- SPRITE ---------- 

//---------- ANIMATED_SPRITE ---------- 

struct animated_sprite
{
    int x;
    int y;
    int w;
    int h;
    double angle;

    SDL_Texture **tex_a;
    int tex_count;
    int tex_active;
    double tex_change_time;
    double tex_change_time_dt;
};

void animated_sprite_init(struct animated_sprite *this, int tex_count);

void animated_sprite_set_dim(struct animated_sprite *this, int x, int y,int w, int h, int angle);

void animated_sprite_load_texture(struct animated_sprite *this, int pos, char *path);

void animated_sprite_draw(struct animated_sprite *this);

void animated_sprite_update(struct animated_sprite *this, double dt);

void animated_sprite_delete(struct animated_sprite *this);

//---------- ANIMATED_SPRITE ---------- 

//graphics
void gfx_draw_texture(SDL_Texture *tex, int x, int y, int w, int h, double angle);

SDL_Texture *gfx_load_texture(char *path);

#endif

//src
#ifndef SPRITE_C

#include "mstd.h"

//---------- SPRITE ---------- 

int sprite_init(struct sprite *this, char *path)
{
    this->x = 0;
    this->y = 0;
    this->w = 30;
    this->h = 30;
    this->angle = 0;

    this->tex = gfx_load_texture(path);
}

void sprite_change_texture(struct sprite *this, char *path)
{
    if(this->tex)
        SDL_DestroyTexture(this->tex);
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

//---------- SPRITE ---------- 


//---------- ANIMATED_SPRITE ---------- 

void animated_sprite_init(struct animated_sprite *this, int tex_count)
{
    this->x = 0;
    this->y = 0;
    this->w = 30;
    this->h = 30;
    this->angle = 0;
    this->tex_count = tex_count;
    this->tex_active = 0;
    this->tex_change_time = 1;
    this->tex_change_time_dt = 0;

    this->tex_a = malloc(sizeof(SDL_Texture*) * tex_count);
    for(int i = 0; i < this->tex_count; i++)
        this->tex_a[i] = 0;
}

void animated_sprite_set_dim(struct animated_sprite *this, int x, int y, int w, int h, int angle)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->angle = angle;
}

void animated_sprite_load_texture(struct animated_sprite *this, int pos, char *path)
{
    if(pos >= this->tex_count)
        return;

    if(this->tex_a[pos])
        SDL_DestroyTexture(this->tex_a[pos]);

    this->tex_a[pos] = gfx_load_texture(path);
}

void animated_sprite_draw(struct animated_sprite *this)
{
    gfx_draw_texture(this->tex_a[this->tex_active], this->x, this->y, this->w, this->h, this->angle);
}

void animated_sprite_update(struct animated_sprite *this, double dt)
{
    this->tex_change_time_dt += dt;
    if(this->tex_change_time_dt >= this->tex_change_time)
    {
        this->tex_change_time_dt -= this->tex_change_time;
        this->tex_active++;
        if(this->tex_active >= this->tex_count)
            this->tex_active = 0;
    }
}

void animated_sprite_delete(struct animated_sprite *this)
{
    for(int i = 0; i < this->tex_count; i++)
        SDL_DestroyTexture(this->tex_a[i]);

    free(this->tex_a);
}


//---------- ANIMATED_SPRITE ---------- 

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

