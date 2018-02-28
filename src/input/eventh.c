//hdr
#ifndef EVENTH_H
#define EVENTH_H
#include "mstd.h"

#define OBJECT_C
#include "object.c"
#undef OBJECT_C

//can also be used for custom SDL User events
struct event_object
{
    struct object *obj;
    void (*update_event)(struct object *obj, SDL_Event *event);
};

void event_object_init(struct event_object *this, struct object *obj, void (*update_event)(struct object *obj, SDL_Event *event));

void event_init();

void event_add_object();

void event_remove_object(int id);

void event_update();

#endif

//src
#ifndef EVENTH_C

struct vector event_object_v;

void event_object_init(struct event_object *this, struct object *obj, void (*update_event)(struct object *obj, SDL_Event *event))
{
    this->obj = obj;
    this->update_event = update_event;
}

void event_init()
{
    vector_init(&event_object_v, sizeof(struct event_object*), 100);
}

void event_add_object(struct event_object *event_obj)
{
    vector_push_back(&event_object_v, event_obj); 
}

void event_remove_object(int id)
{
    for(int i = 0; i < event_object_v.size; i++)
    {
        if(((struct event_object*)vector_at(&event_object_v, i))->obj->id == id)
        {
            vector_remove_at(&event_object_v, i);
            break;
        }
    }
}

void event_update()
{
    SDL_Event sdlevent;
    while(SDL_PollEvent(&sdlevent))
    {
        //todo: handle quit event
        if(sdlevent.type==SDL_QUIT)
        {
            game_container.quit = true;
        }

        struct event_object *temp_event_object;
        for(int i = 0; i < event_object_v.size; i++)
        {
            temp_event_object = vector_at(&event_object_v, i);
            temp_event_object->update_event(temp_event_object->obj, &sdlevent);
        }
    }
}


#endif
