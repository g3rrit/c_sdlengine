//hdr
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

//---------- SCENE
#define SPRITE_C
#include "sprite.c"
#undef SPRITE_C

struct scene
{
    struct sprite *tsprite;
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
    this->tsprite = malloc(sizeof(struct sprite));
    sprite_init(this->tsprite, TEX_TEST);
}

void scene_update(struct scene *this, double dt)
{
    
}

void scene_draw(struct scene *this)
{
    sprite_draw(this->tsprite);
}

void scene_delete(struct scene *this)
{
    free(this->tsprite);
}

//---------- SCENE

void scene_manager_init()
{
    scene_manager.active_scene = malloc(sizeof(struct scene)); 
    scene_init(scene_manager.active_scene);
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
