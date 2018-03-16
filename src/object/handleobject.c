//hdr
#ifndef HANDLEOBJECT_H
#define HANDLEOBJECT_H

#define OBJECT_C
#include "object.c"
#undef OBJECT_C

#define HANDLE_SIZE 4

#define H_UPDATE 0
#define H_DRAW 1
#define H_EVENT 2
#define H_CLICK 3

// ---- HANDLE OBJECT -----

struct handle_object
{
    struct object *obj;
    struct list_node *node;
    void (*fun)(struct object *obj, void *data);
};

void handle_object_init(struct handle_object *this, struct object *obj, void (*fun)(struct object *obj, void *data));

// ---- HANDLE OBJECT -----

// ---- HANDLE -----

void handle_init();

void handle_add(int handle_type, struct handle_object *h_object);

void handle_remove(int handle_type, struct handle_object *h_object);

void handle_dispatch(int handle_type, void *data);

void handle_delete();

// ---- HANDLE FUNCTIONS -----

void event_update();

struct click_data
{
    int x;
    int y;
    int flag;
};

void click_update();

void update_update(double dt);

void draw_update(double dt);

#endif

//src
#ifndef HANDLEOBJECT_C

#include "mstd.h"

struct list handle_array[HANDLE_SIZE];

// ---- HANDLE OBJECT -----

void handle_object_init(struct handle_object *this, struct object *obj, void (*fun)(struct object *obj, void *data))
{
    this->obj = obj;
    this->fun = fun;
}

// ---- HANDLE OBJECT -----

// ---- HANDLE -----

void handle_init()
{
    for(int i = 0; i < HANDLE_SIZE; i++)
        list_init(&(handle_array[i]));
}

#define check_handle_type() if(handle_type < 0 || handle_type >= HANDLE_SIZE) return;

void handle_add(int handle_type, struct handle_object *h_object)
{
    check_handle_type();

    h_object->node = list_push_back(&(handle_array[handle_type]), h_object);
}

void handle_remove(int handle_type, struct handle_object *h_object)
{
    check_handle_type();

    list_remove_node(&(handle_array[handle_type]), h_object->node); 
}

void *for_each_handle_fun(struct handle_object *h_object, void *data, struct list_info *info)
{
    h_object->fun(h_object->obj, data);
    return 0;
}

void handle_dispatch(int handle_type, void *data)
{
    check_handle_type();

    list_for_each(&(handle_array[handle_type]), &for_each_handle_fun, data);
}

void handle_delete()
{
    for(int i = 0; i < HANDLE_SIZE; i++)
        list_delete(&(handle_array[i]));
}

// ---- HANDLE FUNCTIONS -----

void event_update()
{
    SDL_Event sdlevent;
    while(SDL_PollEvent(&sdlevent))
    {
        //handle click events
        if(sdlevent.type == SDL_MOUSEBUTTONDOWN)
            click_update();

        //todo: handle quit event
        if(sdlevent.type==SDL_QUIT)
        {
            game_container.quit = true;
        }

        handle_dispatch(H_EVENT, &sdlevent);
    }

}

void click_update()
{
    int x;
    int y;
    SDL_GetMouseState(&x, &y);

    struct click_data c_data;
    c_data.x = x;
    c_data.y = y;
    c_data.flag = 1;
    handle_dispatch(H_CLICK, &c_data);
}


void update_update(double dt)
{
    handle_dispatch(H_UPDATE, &dt);
}

void draw_update(double dt)
{
    handle_dispatch(H_DRAW, &dt);
}

#endif
