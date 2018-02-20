CC := gcc

SRC_DIR ?= .\src
BUILD_DIR ?= .\build
LIB_DIR ?= .\lib

TARGET := programm

FLAGS := -wall

LIB_SDL_I := .\mingw32sdl\include\SDL2
LIB_SDL_DLL := $(LIB_DIR)\sdl\win64

#-------------------- source

#core
SRCF := .\src\main.c .\src\input\input.c .\src\object\object.c

#objects
SRCF += .\src\object\test_object.c

#util
UTIL := .\util\c-samples\src
SRCF += $(UTIL)\container\container.c

#------------------- includes
INC_DIRS := -I.\src
INC_DIRS += -I$(UTIL)\container
INC_DIRS += -I.\src\input
INC_DIRS += -I.\src\object


all:
	$(CC) -o $(BUILD_DIR)\$(TARGET) $(SRCF) -I$(LIB_SDL_I) $(INC_DIRS) -L.\mingw32sdl\lib -lmingw32 -lSDL2main -lSDL2 

