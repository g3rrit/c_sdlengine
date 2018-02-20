#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mstd.h"

#define INPUT_C
#include "input.c"
#undef INPUT_C

#define TEST_OBJECT_C
#include "test_object.c"
#undef TEST_OBJECT_C

char* randStr(uint32_t length);

int main(int argc, char *argv[])
{
    // ---------- INIT SDL
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        printf("error initing sdl\n");
    }
    printf("sdl inited\n");

    /*
    TTF_Init();
    window.font=TTF_OpenFont("/../res/font/BitFont.ttf",30);
    if(!window.font){
        printf("error loading font\n");
        SDL_Quit();
        TTF_Quit();
        return false;
    }
    */

    SDL_Window* sdlwindow = SDL_CreateWindow("Explore",100,100,800,400,SDL_WINDOW_SHOWN);
    if(!sdlwindow)
    {
        printf("Error creating window");
        SDL_Quit();
        return 0;
    }
    printf("SDL window created \n");
    SDL_Renderer* sdlren = SDL_CreateRenderer(sdlwindow,-1,SDL_RENDERER_ACCELERATED);
    if(sdlren==NULL)
    {
        printf("Error creating renderer");
        SDL_DestroyWindow(sdlwindow);
        SDL_Quit();
        return 0;
    }
    printf("sdl renderer created \n");
    // ---------- INIT SDL

    // ---------- MAIN LOOP
    bool quit = false;
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

    while(!quit)
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
            SDL_RenderClear(sdlren);
            //draw
            //gameContainer.draw();
            SDL_RenderPresent(sdlren);
            frames++;
            render=false;
        }
        else
        {
            usleep(10000);
        }
    }
    // ---------- MAIN LOOP

    // ---------- QUIT SDL
    //TTF_CloseFont(window.font);
    //TTF_Quit();
    SDL_DestroyWindow(sdlwindow);
    SDL_DestroyRenderer(sdlren);
    SDL_Quit();
    // ---------- QUIT SDL

    SDL_Delay(3000);

    return 0;
}



