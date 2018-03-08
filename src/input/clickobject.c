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
    void (*fun)(struct object *obj,int x, int y, int flag);
};

void click_object_init(struct click_object *this, struct object *obj, void (*fun)(struct object *obj, int x, int y, int flag));

void click_init();

void click_add_object(struct click_object *obj);

void click_remove_object(int id);

void click_update();

void click_delete();

#endif

//src
#ifndef CLICKOBJECT_C

#include "mstd.h"

struct vector click_object_v;

void click_object_init(struct click_object *this, struct object *obj, void (*fun)(struct object *obj, int x, int y, int flag))
{
    this->obj = obj;
    this->fun = fun;
}

void click_init()
{
    vector_init(&click_object_v, sizeof(struct click_object*), 10);
}

void click_add_object(struct click_object *c_obj)
{
    vector_push_back(&click_object_v, c_obj);
}

void click_remove_object(int id)
{
    for(int i = 0; i < click_object_v.size; i++)
    {
        if(((struct click_object*)vector_at(&click_object_v, i))->obj->id == id)
        {
            vector_remove_at(&click_object_v, i);
            break;
        }
    }
}

void click_update()
{
    int x;
    int y;
    SDL_GetMouseState(&x, &y);

    struct click_object *temp_click_o;
    for(int i = 0; i < click_object_v.size; i++)
    {
        temp_click_o = vector_at(&click_object_v, i);
        temp_click_o->fun(temp_click_o->obj, x, y, 1);
    }
}

void click_delete()
{
    vector_delete(&click_object_v);
}



#endif
