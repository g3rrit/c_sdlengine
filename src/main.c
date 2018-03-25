#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mstd.h"

#define SCENEMANAGER_C
#include "scenemanager.c"
#undef SCENEMANAGER_C

char* randStr(uint32_t length);

int main(int argc, char *argv[])
{
    game_container_init();

    struct scene p_s;
    scene_init(&p_s);

    scene_manager_push(&p_s);

    game_container_start();
    game_container_delete();

    SDL_Delay(3000);

    return 0;
}



