#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mstd.h"

#ifndef SCENEMANAGER_C
#define SCENEMANAGER_C
#include "scenemanager.c"
#undef SCENEMANAGER_C
#endif

#ifndef TESTSCENE_C
#define TESTSCENE_C
#include "testscene.c"
#undef TESTSCENE_C
#endif

char* randStr(uint32_t length);

int main(int argc, char *argv[])
{
    game_container_init();

    struct test_scene p_s;
    test_scene_init(&p_s);

    scene_manager_push(&p_s);

    game_container_start();
    game_container_delete();

    test_scene_delete(&p_s);

    SDL_Delay(3000);

    return 0;
}



