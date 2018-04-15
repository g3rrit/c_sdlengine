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

#ifndef GOGAMESCENE_C
#define GOGAMESCENE_C
#include "gogamescene.c"
#undef GOGAMESCENE_C
#endif

char* randStr(uint32_t length);

int main(int argc, char *argv[])
{
    game_container_init();

    struct go_game_scene p_s;
    go_game_scene_init(&p_s);

    scene_manager_push(&p_s);

    game_container_start();
    game_container_delete();

    go_game_scene_delete(&p_s);

    SDL_Delay(3000);

    return 0;
}



