//hdr
#ifndef GAMECONTAINER_H
#define GAMECONTAINER_H

#include "SDL.h"

struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    int quit;
} game_container;

int game_container_init();

void game_container_start();

void game_container_delete();

#endif

//src
#ifndef GAMECONTAINER_C

#include "SDL_ttf.h"

#include "mstd.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define INPUT_C
#include "input.c"
#undef INPUT_C

#define TEST_OBJECT_C
#include "test_object.c"
#undef TEST_OBJECT_C

#define SCENEMANAGER_C
#include "scenemanager.c"
#undef SCENEMANAGER_C

#define FONTMANAGER_C
#include "fontmanager.c"
#undef FONTMANAGER_C

int game_container_init()
{
    // ---------- INIT SDL
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        printf("error initing sdl\n");
    }
    printf("sdl inited\n");

    font_manager_init();

    game_container.window = SDL_CreateWindow("Explore",100,100,800,400,SDL_WINDOW_SHOWN);
    if(!game_container.window)
    {
        printf("Error creating window");
        SDL_Quit();
        return 0;
    }
    printf("SDL window created \n");
    game_container.renderer = SDL_CreateRenderer(game_container.window,-1,SDL_RENDERER_ACCELERATED);
    if(game_container.renderer==NULL)
    {
        printf("Error creating renderer");
        SDL_DestroyWindow(game_container.window);
        SDL_Quit();
        return 0;
    }
    printf("sdl renderer created \n");
    // ---------- INIT SDL

    scene_manager_init();
}

void game_container_start()
{
    // ---------- MAIN LOOP
    game_container.quit = false;
    struct timeval currentTime;
    gettimeofday(&currentTime,NULL);
    double lastTime = (currentTime.tv_sec*1000000+currentTime.tv_usec)/1000000.0;
    double firstTime = 0;
    float passedTime = 0;
    float unprocessedTime = 0;
    float frameTime = 0;
    int frames = 0;
    bool render = true;
    float frameCap = 1.0/30.0;
    int FPS = 0;
    //fontManager.add("fpstxt","FPS:",gameState.WIDTH-100,5,60,15);
    //fontManager.add("fpsnum","00",gameState.WIDTH-40,5,40,15);
    input_init();

    //          TEST
    struct test_object t_object;
    test_object_init(&t_object);

    input_add_object(&(t_object.input_obj));
    //          TEST

    while(!game_container.quit)
    {

        //update input
        input_update();

        gettimeofday(&currentTime,NULL);
        firstTime=(currentTime.tv_sec*1000000+currentTime.tv_usec)/1000000.0;
        passedTime=firstTime-lastTime;
        lastTime=firstTime;
        unprocessedTime=unprocessedTime+(float)passedTime;
        frameTime=frameTime+passedTime;
        while(unprocessedTime>=frameCap)
        {
            //update
            //gameContainer.update((float)frameCap);
            scene_manager_update(frameCap);

            unprocessedTime=unprocessedTime-frameCap;
            render=true;
            if(frameTime>=1)
            {
                char fpsnum[12];
                snprintf(fpsnum,12,"%d",FPS);
                //fontManager.setText("fpsnum",&fpsnum);
                frameTime=0;
                FPS=frames;
                frames=0;
            }
        }
        if(render)
        {
            SDL_RenderClear(game_container.renderer);
            //draw
            //gameContainer.draw();
            scene_manager_draw();
            SDL_RenderPresent(game_container.renderer);
            frames++;
            render=false;
        }
        else
        {
            usleep(10000);
        }
    }
    // ---------- MAIN LOOP
}

void game_container_delete()
{
    scene_manager_delete();
    font_manager_delete();
    // ---------- QUIT SDL
    SDL_DestroyWindow(game_container.window);
    SDL_DestroyRenderer(game_container.renderer);
    SDL_Quit();
    // ---------- QUIT SDL
}


#endif
