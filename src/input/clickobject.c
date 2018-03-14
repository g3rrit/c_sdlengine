//hdr
#ifndef CLICKOBJECT_H
#define CLICKOBJECT_H

#define OBJECT_C
#include "object.c"
#undef OBJECT_C

// click function flags
#define CLICK_LEFT 1
//...

struct click_object
{
    struct object *obj;
    struct list_node *node;
    void (*fun)(struct object *obj,int x, int y, int flag);
};

void click_object_init(struct click_object *this, struct object *obj, void (*fun)(struct object *obj, int x, int y, int flag));

void click_init();

void click_add_object(struct click_object *c_obj);

void click_remove_object(struct click_object *c_obj);

void click_update();

void click_delete();

#endif

//src
#ifndef CLICKOBJECT_C

#include "mstd.h"

struct list click_object_l;

void click_object_init(struct click_object *this, struct object *obj, void (*fun)(struct object *obj, int x, int y, int flag))
{
    this->obj = obj;
    this->fun = fun;
}

void click_init()
{
    list_init(&click_object_l);
}

void click_add_object(struct click_object *c_obj)
{
    c_obj->node = list_push_back(&click_object_l, c_obj);
}

void click_remove_object(struct click_object *c_obj)
{
    list_remove_node(&click_object_l, c_obj->node);
    /*
    for(int i = 0; i < click_object_l.size; i++)
    {
        if(((struct click_object*)list_at(&click_object_l, i))->obj->id == id)
        {
            list_remove_at(&click_object_l, i);
            break;
        }
    }
    */
}

struct click_event_s
{
    int x;
    int y;
    int flag;
};

void *for_each_click_update(struct click_object *c_obj, struct click_event_s *c_ev, struct list_info *info)
{
    c_obj->fun(c_obj->obj, c_ev->x, c_ev->y, c_ev->flag);
    return 0;
}


void click_update()
{
    int x;
    int y;
    SDL_GetMouseState(&x, &y);

    struct click_event_s c_ev;
    c_ev.x = x;
    c_ev.y = y;
    c_ev.flag = 1;
    list_for_each(&click_object_l, &for_each_click_update, &c_ev);
    /*
    struct click_object *temp_click_o;
    for(int i = 0; i < click_object_l.size; i++)
    {
        temp_click_o = list_at(&click_object_l, i);
        temp_click_o->fun(temp_click_o->obj, x, y, 1);
    }
    */
}

void click_delete()
{
    list_delete(&click_object_l);
}



#endif
