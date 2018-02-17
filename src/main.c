#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "mstd.h"

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
    SDL_Event sdlevent;
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
    while(!quit)
    {
        while(SDL_PollEvent(&sdlevent))
        {
            if(sdlevent.type==SDL_QUIT)
            {
                quit=true;
            }
            else if(sdlevent.type==SDL_KEYDOWN)
            {
            }
            else if(sdlevent.type==SDL_MOUSEBUTTONDOWN)
            {
            }
        }
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


char* randStr(uint32_t length)
{
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* res = malloc(sizeof(char)*(length));
    res[length-1]=0;
    length--;
    while(length>0)
    {
        uint32_t index = (double)rand()/RAND_MAX*(sizeof(charset)-1);
        res[length-1]=charset[index];
        length--;
    }
    printf("random string: %s\n",res);
    return res;
}
