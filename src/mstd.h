//hdr
#ifndef MSTD_H
#define MSTD_H

#include "SDL.h"
#include "SDL_image.h"

#include "stdio.h"
#include "stdlib.h"

#ifndef CONTAINER_C
#define CONTAINER_C
#include "container.c"
#undef CONTAINER_C
#endif

#ifndef MAP_C
#define MAP_C
#include "map.c"
#undef MAP_C
#endif

#ifndef LIST_C
#define LIST_C
#include "list.c"
#undef LIST_C
#endif

#ifndef VECTOR_C
#define VECTOR_C
#include "vector.c"
#undef VECTOR_C
#endif

#ifndef GAMECONTAINER_C
#define GAMECONTAINER_C
#include "gamecontainer.c"
#undef GAMECONTAINER_C
#endif

#ifndef HANDLEOBJECT_C
#define HANDLEOBJECT_C
#include "handleobject.c"
#undef HANDLEOBJECT_C
#endif

#include "texture_def.h"

typedef int bool;
#define true 1
#define false 0

#endif
