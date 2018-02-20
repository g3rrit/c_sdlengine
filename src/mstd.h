//hdr
#ifndef MSTD_H
#define MSTD_H

#include "SDL.h"

#include "stdio.h"
#include "stdlib.h"

#define CONTAINER_C
#include "container.c"
#undef CONTAINER_C

typedef int bool;
#define true 1
#define false 0

#endif
