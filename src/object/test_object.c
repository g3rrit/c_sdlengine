//hdr
#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#define OBJECT_C
#include "object.c"
#undef OBJECT_C

#include "mstd.h"


//---------- TESTOBJECT ---------- 

struct test_object
{
    struct object obj;
    struct handle_object event_obj;
    struct handle_object click_obj;
};

void test_object_init(struct test_object *this);


//---------- TESTOBJECT ---------- 

#endif

//src
#ifndef TEST_OBJECT_C


//---------- TESTOBJECT ---------- 

void test_object_update_event(struct object *obj, SDL_Event *event);

void test_object_click_fun(struct object *obj, struct click_data *c_data);

void test_object_init(struct test_object *this)
{
    object_init(&(this->obj), this);
    handle_object_init(&(this->event_obj), &(this->obj), &test_object_update_event);
    handle_object_init(&(this->click_obj), &(this->obj), &test_object_click_fun);
    handle_add(H_CLICK, &(this->click_obj));
    handle_add(H_EVENT, &(this->event_obj));
}

void test_object_update_event(struct object *obj, SDL_Event *event)
{
    if(event->type == SDL_KEYDOWN)
    {
        printf("in test_object_update_event\n");
        printf("object id: %i\n", obj->id);
    }

    if(event->key.keysym.sym == SDLK_a)
    {
        printf("pressed a button -> removing object from event vector\n");
        struct test_object *t_ob = obj->super;
        handle_remove(H_EVENT, &t_ob->event_obj);
        printf("error here\n");
    }
}

void test_object_click_fun(struct object *obj, struct click_data *c_data)
{
    printf("clicked at (%i,%i) flag: %i\n", c_data->x, c_data->y, c_data->flag);
}

//---------- TESTOBJECT ---------- 

#endif
