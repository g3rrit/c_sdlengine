//hdr
#ifndef TESTSCENE_H
#define TESTSCENE_H

//---------- SCENE
#ifndef SPRITE_C
#define SPRITE_C
#include "sprite.c"
#undef SPRITE_C
#endif

#ifndef TEXT_C
#define TEXT_C
#include "text.c"
#undef TEXT_C
#endif

#ifndef SCENE_C
#define SCENE_C
#include "scene.c"
#undef SCENE_C
#endif

#ifndef TETS_OBJECT_C
#define TEST_OBJECT_C
#include "test_object.c"
#undef TEST_OBJECT_C
#endif

struct test_scene
{
    struct scene scene_i;
    struct object obj;

    struct test_object t_object;

    struct sprite *tsprite;
    struct animated_sprite *tasprite;
    struct text *ttext;

    struct handle_object h_update;
    struct handle_object h_draw;
};

void test_scene_init(struct test_scene *this);

void test_scene_update(struct object *obj, double *dt);

void test_scene_draw(struct object *obj, double *dt);

void test_scene_delete(struct test_scene *this);

//---------- SCENE


#endif

//src
#ifndef TESTSCENE_C

//---------- SCENE

void test_scene_init(struct test_scene *this)
{
    printf("test_scene_init\n");
    scene_init(&(this->scene_i), this);
    object_init(&(this->obj), this, &(this->scene_i));

    //sprite test
    this->tsprite = malloc(sizeof(struct sprite));
    sprite_init(this->tsprite, TEX_TEST);

    //text test
    this->ttext = malloc(sizeof(struct text));
    text_init(this->ttext, "hello world");

    //animated_sprite test
    this->tasprite = malloc(sizeof(struct animated_sprite));
    animated_sprite_init(this->tasprite, 3);
    animated_sprite_set_dim(this->tasprite, 50, 50, 40, 40, 0);
    animated_sprite_load_texture(this->tasprite, 0, TEX_TEST);
    animated_sprite_load_texture(this->tasprite, 1, TEX_TEST2);
    animated_sprite_load_texture(this->tasprite, 2, TEX_TEST3);

    test_object_init(&(this->t_object), &(this->scene_i));

    handle_object_init(&(this->h_update), &(this->obj), &test_scene_update);
    handle_object_init(&(this->h_draw), &(this->obj), &test_scene_draw);
    scene_add_handle(&(this->scene_i), H_UPDATE, &(this->h_update));
    scene_add_handle(&(this->scene_i), H_DRAW, &(this->h_draw));
    printf("test_scene_init end\n");
}

void test_scene_update(struct object *obj, double *dt)
{
    struct test_scene *this = obj->super;
    animated_sprite_update(this->tasprite, *dt); 
}

void test_scene_draw(struct object *obj, double *dt)
{
    struct test_scene *this = obj->super;
    sprite_draw(this->tsprite);
    animated_sprite_draw(this->tasprite);
    text_draw(this->ttext);
}

void test_scene_delete(struct test_scene *this)
{
    sprite_delete(this->tsprite);
    free(this->tsprite);
    text_delete(this->ttext);
    free(this->ttext);
    animated_sprite_delete(this->tasprite);
    free(this->tasprite);
}

//---------- SCENE

#endif
