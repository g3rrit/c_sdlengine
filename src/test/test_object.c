//hdr
#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#ifndef OBJECT_C
#define OBJECT_C
#include "object.c"
#undef OBJECT_C
#endif

#include "mstd.h"


//---------- TESTOBJECT ---------- 

struct test_object
{
    struct object obj;
    struct handle_object event_obj;
    struct handle_object click_obj;
};

void test_object_init(struct test_object *this, struct scene *scene_o);


//---------- TESTOBJECT ---------- 

#endif

//src
#ifndef TEST_OBJECT_C


//---------- TESTOBJECT ---------- 

void test_object_update_event(struct object *obj, SDL_Event *event);

void test_object_click_fun(struct object *obj, struct click_data *c_data);

void test_object_init(struct test_object *this, struct scene *scene_o)
{
    object_init(&(this->obj), this, scene_o);
    handle_object_init(&(this->event_obj), &(this->obj), &test_object_update_event);
    handle_object_init(&(this->click_obj), &(this->obj), &test_object_click_fun);
    scene_add_handle(this->obj.scene_o, H_CLICK, &(this->click_obj));
    scene_add_handle(this->obj.scene_o, H_EVENT, &(this->event_obj));
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
        scene_remove_handle(obj->scene_o, H_EVENT, &t_ob->event_obj);
        printf("error here\n");
    }

    if(event->key.keysym.sym == SDLK_q)
    {
        printf("pressed q button -> removing active scene from scenemanager\n");

        scene_manager_pop();

        printf("successfully poped scene of scenemanager\n");
    }
}

void test_object_click_fun(struct object *obj, struct click_data *c_data)
{
    printf("clicked at (%i,%i) flag: %i\n", c_data->x, c_data->y, c_data->flag);
}

//---------- TESTOBJECT ---------- 

#endif
