//hdr
#ifndef EVENTOBJECT_H
#define EVENTOBJECT_H
#include "mstd.h"

#define OBJECT_C
#include "object.c"
#undef OBJECT_C

//can also be used for custom SDL User events
struct event_object
{
    struct object *obj;
    struct list_node *node;
    void (*update_event)(struct object *obj, SDL_Event *event);
};

void event_object_init(struct event_object *this, struct object *obj, void (*update_event)(struct object *obj, SDL_Event *event));

void event_init();

void event_add_object(struct event_object *event_obj);

void event_remove_object(struct event_object *event_obj);

void event_update();

void event_delete();

#endif

//src
#ifndef EVENTOBJECT_C

#define CLICKOBJECT_C
#include "clickobject.c"
#undef CLICKOBJECT_C

struct list event_object_l;

void event_object_init(struct event_object *this, struct object *obj, void (*update_event)(struct object *obj, SDL_Event *event))
{
    this->obj = obj;
    this->update_event = update_event;
}

void event_init()
{
    list_init(&event_object_l);
}

void event_add_object(struct event_object *event_obj)
{
    event_obj->node = list_push_back(&event_object_l, event_obj); 
}

void event_remove_object(struct event_object *event_obj)
{
    list_remove_node(&event_object_l, event_obj->node);
    /*
    for(int i = 0; i < event_object_l.size; i++)
    {
        if(((struct event_object*)list_at(&event_object_l, i))->obj->id == id)
        {
            list_remove_at(&event_object_l, i);
            break;
        }
    }
    */
}

void *for_each_event_update(struct event_object *data, SDL_Event *event, struct list_info *info)
{
    data->update_event(data->obj, event);
}

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

        list_for_each(&event_object_l, &for_each_event_update, &sdlevent);
        /*
        struct event_object *temp_event_object;
        for(int i = 0; i < event_object_l.size; i++)
        {
            temp_event_object = list_at(&event_object_l, i);
            temp_event_object->update_event(temp_event_object->obj, &sdlevent);
        }
        */
    }
}

void event_delete()
{
    list_delete(&event_object_l);
}

#endif
