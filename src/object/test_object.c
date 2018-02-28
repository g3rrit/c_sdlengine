//hdr
#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#define EVENTH_C
#include "eventh.c"
#undef EVENTH_C


#define OBJECT_C
#include "object.c"
#undef OBJECT_C

//---------- TESTOBJECT ---------- 

struct test_object
{
    struct object obj;
    struct event_object event_obj;
};

void test_object_init(struct test_object *this);


//---------- TESTOBJECT ---------- 

#endif

//src
#ifndef TEST_OBJECT_C

//---------- TESTOBJECT ---------- 

void test_object_update_event(struct object *obj, SDL_Event *event);

void test_object_init(struct test_object *this)
{
    object_init(&(this->obj), this);
    event_object_init(&(this->event_obj), &(this->obj), &test_object_update_event);
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
        event_remove_object(obj->id);
    }
}

//---------- TESTOBJECT ---------- 

#endif
