CC := gcc

SRC_DIR ?= .\src
BUILD_DIR ?= .\build
LIB_DIR ?= .\lib

TARGET := programm

FLAGS := -wall

LIB_SDL_I := .\mingw32sdl\include\SDL2
LIB_SDL_DLL := $(LIB_DIR)\sdl\win64

SRCF := $(shell find $(SRC_DIR) -name *.c)

INC_DIRS := $(SRC_DIR)

all:
	$(CC) -o $(BUILD_DIR)\$(TARGET) .\src\main.c -I$(LIB_SDL_I) -I$(INC_DIRS) -L.\mingw32sdl\lib -lmingw32 -lSDL2main -lSDL2 

