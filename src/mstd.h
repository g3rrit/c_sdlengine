//hdr
#ifndef MSTD_H
#define MSTD_H

#include "SDL.h"
#include "SDL_image.h"

#include "stdio.h"
#include "stdlib.h"

#define CONTAINER_C
#include "container.c"
#undef CONTAINER_C

#define GAMECONTAINER_C
#include "gamecontainer.c"
#undef GAMECONTAINER_C

#include "texture_def.h"

typedef int bool;
#define true 1
#define false 0

#endif
