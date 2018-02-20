//hdr
#ifndef INPUT_H
#define INPUT_H
#include "mstd.h"

#define OBJECT_C
#include "object.c"
#undef OBJECT_C

struct input_object
{
    struct object *obj;
    void (*update_input)(struct object *obj, SDL_Event *event);
};

void input_object_init(struct input_object *this, struct object *obj, void (*update_input)(struct object *obj, SDL_Event *event));

void input_init();

void input_add_object();

void input_update();

#endif

//src
#ifndef INPUT_C

struct vector input_object_v;

void input_object_init(struct input_object *this, struct object *obj, void (*update_input)(struct object *obj, SDL_Event *event))
{
    this->obj = obj;
    this->update_input = update_input;
}

void input_init()
{
    vector_init(&input_object_v, sizeof(struct input_object*), 100);
}

void input_add_object(struct input_object *input_obj)
{
    vector_push_back(&input_object_v, input_obj); 
}

void input_update()
{
    SDL_Event sdlevent;
    while(SDL_PollEvent(&sdlevent))
    {
        //todo: handle quit event
        if(sdlevent.type==SDL_QUIT)
        {
        }

        struct input_object *temp_input_object;
        for(int i = 0; i < input_object_v.size; i++)
        {
            temp_input_object = vector_at(&input_object_v, i);
            temp_input_object->update_input(temp_input_object->obj, &sdlevent);
        }
    }
}


#endif
