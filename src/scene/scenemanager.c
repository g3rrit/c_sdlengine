//hdr
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

//---------- SCENE
#define SPRITE_C
#include "sprite.c"
#undef SPRITE_C

#define TEXT_C
#include "text.c"
#undef TEXT_C

struct scene
{
    struct sprite *tsprite;
    struct animated_sprite *tasprite;
    struct text *ttext;
    int id; 
};

void scene_init(struct scene *this);

void scene_update(struct scene *this, double dt);

void scene_draw(struct scene *this);

void scene_delete(struct scene *this);

//---------- SCENE

struct 
{
    struct scene *active_scene;
} scene_manager;

void scene_manager_init();

void scene_manager_push(struct scene *p_s);

void scene_manager_pop();

void scene_manager_update(double dt);

void scene_manager_draw();

void scene_manager_delete();

#endif

//src
#ifndef SCENEMANAGER_C

#include "mstd.h"

//---------- SCENE

void scene_init(struct scene *this)
{
    //sprite test
    this->tsprite = malloc(sizeof(struct sprite));
    sprite_init(this->tsprite, TEX_TEST);

    //text test
    this->ttext = malloc(sizeof(struct text));
    //text_init(this->ttext, "hello world");

    //animated_sprite test
    this->tasprite = malloc(sizeof(struct animated_sprite));
    animated_sprite_init(this->tasprite, 3);
    animated_sprite_set_dim(this->tasprite, 50, 50, 40, 40, 0);
    animated_sprite_load_texture(this->tasprite, 0, TEX_TEST);
    animated_sprite_load_texture(this->tasprite, 1, TEX_TEST2);
    animated_sprite_load_texture(this->tasprite, 2, TEX_TEST3);
}

void scene_update(struct scene *this, double dt)
{
    animated_sprite_update(this->tasprite, dt); 
}

void scene_draw(struct scene *this)
{
    sprite_draw(this->tsprite);
    animated_sprite_draw(this->tasprite);
    //text_draw(this->ttext);
}

void scene_delete(struct scene *this)
{
    sprite_delete(this->tsprite);
    free(this->tsprite);
    //text_delete(this->ttext);
    free(this->ttext);
    animated_sprite_delete(this->tasprite);
    free(this->tasprite);
}

//---------- SCENE

void scene_manager_init()
{
}

void scene_manager_push(struct scene *p_s)
{
    scene_manager.active_scene = p_s;
}

void scene_manager_pop()
{
}

void scene_manager_update(double dt)
{
    scene_update(scene_manager.active_scene, dt);
}

void scene_manager_draw()
{
    scene_draw(scene_manager.active_scene);
}

void scene_manager_delete()
{
    free(scene_manager.active_scene);
}

#endif
