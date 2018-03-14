//hdr
#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#define EVENTOBJECT_C
#include "eventobject.c"
#undef EVENTOBJECT_C

#define CLICKOBJECT_C
#include "clickobject.c"
#undef CLICKOBJECT_C


#define OBJECT_C
#include "object.c"
#undef OBJECT_C


//---------- TESTOBJECT ---------- 

struct test_object
{
    struct object obj;
    struct event_object event_obj;
    struct click_object click_obj;
};

void test_object_init(struct test_object *this);


//---------- TESTOBJECT ---------- 

#endif

//src
#ifndef TEST_OBJECT_C

//---------- TESTOBJECT ---------- 

void test_object_update_event(struct object *obj, SDL_Event *event);

void test_object_click_fun(struct object *obj, int x, int y, int flag);

void test_object_init(struct test_object *this)
{
    object_init(&(this->obj), this);
    event_object_init(&(this->event_obj), &(this->obj), &test_object_update_event);
    click_object_init(&(this->click_obj), &(this->obj), &test_object_click_fun);
    click_add_object(&(this->click_obj));
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
        event_remove_object(&t_ob->event_obj);
    }
}

void test_object_click_fun(struct object *obj, int x, int y, int flag)
{
    printf("clicked at (%i,%i) flag: %i\n", x, y, flag);
}

//---------- TESTOBJECT ---------- 

#endif
