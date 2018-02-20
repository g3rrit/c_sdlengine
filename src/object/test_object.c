//hdr
#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#define INPUT_C
#include "input.c"
#undef INPUT_C


#define OBJECT_C
#include "object.c"
#undef OBJECT_C

//---------- TESTOBJECT ---------- 

struct test_object
{
    struct object obj;
    struct input_object input_obj;
};

void test_object_init(struct test_object *this);


//---------- TESTOBJECT ---------- 

#endif

//src
#ifndef TEST_OBJECT_C

//---------- TESTOBJECT ---------- 

void test_object_update_input(struct object *obj, SDL_Event *event);

void test_object_init(struct test_object *this)
{
    object_init(&(this->obj), this);
    input_object_init(&(this->input_obj), &(this->obj), &test_object_update_input);
}

void test_object_update_input(struct object *obj, SDL_Event *event)
{
    if(event->type == SDL_KEYDOWN)
    {
        printf("in test_object_update_input\n");
        printf("object id: %s\n", obj->id);
    }
}

//---------- TESTOBJECT ---------- 

#endif
