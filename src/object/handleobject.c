//hdr
#ifndef HANDLEOBJECT_H
#define HANDLEOBJECT_H

#ifndef OBJECT_C
#define OBJECT_C
#include "object.c"
#undef OBJECT_C
#endif

#define HANDLE_SIZE 4

#define H_UPDATE 0
#define H_DRAW 1
#define H_EVENT 2
#define H_CLICK 3

// ---- HANDLE OBJECT -----

struct handle_object
{
    struct object *obj;
    struct list_node *node;
    void (*fun)(struct object *obj, void *data);
};

void handle_object_init(struct handle_object *this, struct object *obj, void (*fun)(struct object *obj, void *data));

// ---- HANDLE OBJECT -----

// ---- HANDLE -----

struct handle
{
    struct list *handle_array;
    int size;
};

void handle_init(struct handle *this, int size);

void handle_add(struct handle *this, int handle_type, struct handle_object *h_object);

void handle_remove(struct handle *this, int handle_type, struct handle_object *h_object);

void handle_dispatch(struct handle *this, int handle_type, void *data);

void handle_delete(struct handle *this);

struct click_data
{
    int x;
    int y;
    int flag;
};

#endif

//src
#ifndef HANDLEOBJECT_C

#include "mstd.h"

// ---- HANDLE OBJECT -----

void handle_object_init(struct handle_object *this, struct object *obj, void (*fun)(struct object *obj, void *data))
{
    this->obj = obj;
    this->fun = fun;
}

// ---- HANDLE OBJECT -----

// ---- HANDLE -----

void handle_init(struct handle *this, int size)
{
    this->handle_array = malloc(sizeof(struct list) * size);
    this->size = size;

    for(int i = 0; i < size; i++)
        list_init(&(this->handle_array[i]));
}

#define check_handle_type() if(handle_type < 0 || handle_type >= this->size) return;

void handle_add(struct handle *this, int handle_type, struct handle_object *h_object)
{
    check_handle_type();

    h_object->node = list_push_back(&(this->handle_array[handle_type]), h_object);
}

void handle_remove(struct handle *this, int handle_type, struct handle_object *h_object)
{
    check_handle_type();

    list_remove_node(&(this->handle_array[handle_type]), h_object->node); 
}

void *for_each_handle_fun(struct handle_object *h_object, void *data, struct list_info *info)
{
    h_object->fun(h_object->obj, data);
    return 0;
}

void handle_dispatch(struct handle *this, int handle_type, void *data)
{
    check_handle_type();

    list_for_each(&(this->handle_array[handle_type]), &for_each_handle_fun, data);
}

void handle_delete(struct handle *this)
{
    for(int i = 0; i < HANDLE_SIZE; i++)
        list_delete(&(this->handle_array[i]));

    if(this->handle_array)
        free(this->handle_array);

    this->size = 0;
}

#endif
