#ifndef BOARDOBJECT_H
#define BOARDOBJECT_H

#ifndef OBJECT_C
#define OBJECT_C
#include "object.c"
#undef OBJECT_C
#endif

#ifndef SPRITE_C
#define SPRITE_C
#include "sprite.c"
#undef SPRITE_C
#endif

#include "mstd.h"

#define BOARD_SIZE 361
#define BOARD_LENGTH 19

#define BOARD_LENGTH_P 400

struct board_object
{
    struct object obj;

    struct scene *scene_i;

    unsigned char board_state[BOARD_SIZE];     // 19 x 19 places

    int x_pos;
    int y_pos;

    int length;

    //white player is 0 black player is 1
    int active_player;

    struct sprite board_sprite;

    struct handle_object h_update;
    struct handle_object h_draw; 
    struct handle_object h_click;
};

#define NO_STONE 0
#define WHITE_STONE 1
#define BLACK_STONE 2

#include "texture_def.h"

void board_object_init(struct board_object *this, struct scene *scene_i);

void board_object_update(struct board_object *this, double *dt);

void board_object_draw(struct board_object *this, double *dt);

void board_object_click(struct board_object *this, struct click_data *c_data);

//return 1 - valid move | 0 - not a valid move
int board_object_set_at(struct board_object *this, int x, int y, unsigned char stone_type);

unsigned char board_object_get_at(struct board_object *this, int x, int y);

void board_object_delete(struct board_object *this);

#endif

//src
#ifndef BOARDOBJECT_C

void board_object_init(struct board_object *this, struct scene *scene_i)
{
    printf("board object init\n");

    this->x_pos = 0;
    this->y_pos = 0;
    this->length = BOARD_LENGTH_P;

    this->active_player = 0;

    this->scene_i = scene_i;

    object_init(&this->obj, this, scene_i);

    sprite_init(&this->board_sprite, BOARD_TEX);
    printf("board sprite inited\n");

    handle_object_init(&this->h_update, &this->obj, &board_object_update);
    handle_object_init(&this->h_draw, &this->obj, &board_object_draw);
    handle_object_init(&this->h_click, &this->obj, &board_object_click);

    printf("board handle objects inited\n");

    scene_add_handle(this->scene_i, H_UPDATE, &this->h_update);
    scene_add_handle(this->scene_i, H_DRAW, &this->h_draw);
    scene_add_handle(this->scene_i, H_CLICK, &this->h_click);

    memset(this->board_state, 0, BOARD_SIZE);

    printf("board object inited\n");
}

void board_object_update(struct board_object *this, double *dt)
{
}

void board_object_draw(struct board_object *this, double *dt)
{
    sprite_draw(&this->board_sprite);
}

void board_object_click(struct board_object *this, struct click_data *c_data)
{
    int x_c = c_data->x - this->x_pos;
    int y_c = c_data->y - this->y_pos;

    if(x_c >= this->length || x_c < 0 || y_c >= this->length || y_c < 0)
        return 0;

    board_object_set_at(this, x_c / BOARD_LENGTH, y_c / BOARD_LENGTH, this->active_player + 1);
}

int board_object_set_at(struct board_object *this, int x, int y, unsigned char stone_type)
{
    if(x >= BOARD_LENGTH || x < 0 || y >= BOARD_LENGTH || y < 0)
        return 0;

    if(stone_type >= 3)
        return 0;

    this->board_state[y * BOARD_LENGTH + x] = stone_type;
}

unsigned char board_object_get_at(struct board_object *this, int x, int y)
{
    if(x >= BOARD_LENGTH || x < 0 || y >= BOARD_LENGTH || y < 0)
        return 0;

    return this->board_state[y * BOARD_LENGTH + x];
}

void board_object_delete(struct board_object *this)
{
}



#endif
