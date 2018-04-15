//hdr
#ifndef GOGAMESCENE_H
#define GOGAMESCENE_H

#ifndef OBJECT_C
#define OBJECT_C
#include "object.c"
#undef OBJECT_C
#endif

#ifndef SCENE_C
#define SCENE_C
#include "scene.c"
#undef SCENE_C
#endif

#ifndef BOARDOBJECT_C
#define BOARDOBJECT_C
#include "boardobject.c"
#undef BOARDOJECT_C
#endif

#ifndef HANDLEOBJECT_C
#define HANDLEOBJECT_C
#include "handleobject.c"
#undef HANDLEOBJECT_C
#endif

#include "mstd.h"

struct go_game_scene
{
    struct scene scene_i;
    struct object obj;

    struct board_object b_object;

    struct handle_object h_update;
    struct handle_object h_draw;
};

void go_game_scene_init(struct go_game_scene *this);

void go_game_scene_update(struct go_game_scene *this, double *dt);

void go_game_scene_draw(struct go_game_scene *this, double *dt);

void go_game_scene_delete(struct go_game_scene *this);

#endif

//src
#ifndef GOGAMESCENE_C

void go_game_scene_init(struct go_game_scene *this)
{
    printf("go game scene init\n");

    scene_init(&this->scene_i, this); 

    object_init(&this->obj, this, &this->scene_i);

    board_object_init(&this->b_object, &this->scene_i);

    handle_object_init(&this->h_update, &this->obj, &go_game_scene_update);
    handle_object_init(&this->h_draw, &this->obj, &go_game_scene_draw);

    scene_add_handle(&this->scene_i, H_UPDATE, &this->h_update);
    scene_add_handle(&this->scene_i, H_DRAW, &this->h_draw);

    printf("go game scene inited\n");
}

void go_game_scene_update(struct go_game_scene *this, double *dt)
{
}

void go_game_scene_draw(struct go_game_scene *this, double *dt)
{
}

void go_game_scene_delete(struct go_game_scene *this)
{
    board_object_delete(&this->b_object);

    scene_delete(&this->scene_i);
}

#endif
