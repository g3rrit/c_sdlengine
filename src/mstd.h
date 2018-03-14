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

#define MAP_C
#include "map.c"
#undef MAP_C

#define LIST_C
#include "list.c"
#undef LIST_C

#define VECTOR_C
#include "vector.c"
#undef VECTOR_C

#define GAMECONTAINER_C
#include "gamecontainer.c"
#undef GAMECONTAINER_C

#include "texture_def.h"

typedef int bool;
#define true 1
#define false 0

#endif
