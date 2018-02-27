#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mstd.h"

char* randStr(uint32_t length);

int main(int argc, char *argv[])
{
    game_container_init();
    game_container_start();
    game_container_delete();

    SDL_Delay(3000);

    return 0;
}



