//hdr
#ifndef OBJECT_H
#define OBJECT_H

#include "mstd.h"

//---------- OBJECT ---------- 

struct object
{
    int id;
    void *super;
};

void object_init(struct object *this, void *super);

void object_delete(struct object *this);

//---------- OBJECT ---------- 

char* rand_str(uint32_t length);

#endif

//src
#ifndef OBJECT_C

int current_object_id = 0;

//---------- OBJECT ---------- 

void object_init(struct object *this, void *super)
{
    this->super = super;
    this->id = current_object_id;
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
