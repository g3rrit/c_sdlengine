//hdr
#ifndef OBJECT_H
#define OBJECT_H

//---------- OBJECT ---------- 
#include "stdint.h"

#ifndef SCENE_C
#define SCENE_C
#include "scene.c"
#undef SCENE_C
#endif

struct object
{
    int id;
    void *super;

    struct scene *scene_o;
};

void object_init(struct object *this, void *super, struct scene *scene_o);

void object_delete(struct object *this);

//---------- OBJECT ---------- 

char* rand_str(uint32_t length);

#endif

//src
#ifndef OBJECT_C

#include "stdlib.h"

int current_object_id = 0;

//---------- OBJECT ---------- 

void object_init(struct object *this, void *super, struct scene *scene_o)
{
    this->super = super;
    this->id = current_object_id;
    this->scene_o = scene_o;
    current_object_id++;
}

void object_delete(struct object *this)
{
}

//---------- OBJECT ---------- 

char* rand_str(uint32_t length)
{
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* res = malloc(sizeof(char)*(length));
    res[length-1]=0;
    length--;
    while(length>0)
    {
        uint32_t index = (double)rand()/RAND_MAX*(sizeof(charset)-1);
        res[length-1]=charset[index];
        length--;
    }
    printf("random string: %s\n",res);
    return res;
}

#endif
