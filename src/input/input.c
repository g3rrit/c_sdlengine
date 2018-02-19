//hdr
#ifndef INPUT_H
#define INPUT_H
#include "mstd.h"

#define STATE_PRESSED 1

void input_add(char *id, void *(*fun)(int state));

#endif

//src
#ifndef INPUT_C

#define INPUT_SIZE 10

struct map _input_arr[INPUT_SIZE];

#endif
