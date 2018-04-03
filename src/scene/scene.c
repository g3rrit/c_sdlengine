//hdr
#ifndef SCENE_H
#define SCENE_H

#include "mstd.h"

#ifndef HANDLEOBJECT_C
#define HANDLEOBJECT_C
#include "handleobject.c"
#undef HANDLEOBJECT_C
#endif

#define HANDLE_SIZE 7
#define H_UPDATE 0
#define H_DRAW 1
#define H_START 2
#define H_STOP 3
#define H_EVENT 4
#define H_CLICK 5
#define H_CHANGE_STATE 6


struct scene
{
    void *super;

    int state;

    struct handle *scene_handle;
};

void scene_init(struct scene *this, void *super);

void scene_add_handle(struct scene *this, int handle_type, struct handle_object *h_object);

void scene_remove_handle(struct scene *this, int handle_type, struct handle_object *h_object);

void scene_dispatch_handle(struct scene *this, int handle_type, void *data);

void scene_change_state(struct scene *this, int new_state);

void scene_delete(struct scene *this);

#endif

//src
#ifndef SCENE_C

void scene_init(struct scene *this, void *super)
{
    this->super = super;
    this->scene_handle = malloc(sizeof(struct handle));
    this->state = 0;
    handle_init(this->scene_handle, HANDLE_SIZE);
}

void scene_add_handle(struct scene *this, int handle_type, struct handle_object *h_object)
{
    handle_add(this->scene_handle, handle_type, h_object);
}

void scene_remove_handle(struct scene *this, int handle_type, struct handle_object *h_object)
{
    handle_remove(this->scene_handle, handle_type, h_object);
}

void scene_dispatch_handle(struct scene *this, int handle_type, void *data)
{
    handle_dispatch(this->scene_handle, handle_type, data);
}

void scene_change_state(struct scene *this, int new_state)
{
    this->state = new_state;
    handle_dispatch(this->scene_handle, H_CHANGE_STATE, new_state);
}

void scene_delete(struct scene *this)
{
    handle_delete(this->scene_handle);
    if(this->scene_handle)
        free(this->scene_handle);
}

#endif
