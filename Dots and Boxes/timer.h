#ifndef TIMER_H
#define TIMER_H
#include <time.h>
#include "showMainMenu.h"

//show timer function
void showTime(SDL_Renderer *renderer){
    clock_t newtime=clock()-oldTime; //old time starts when grid is shown, newtime is gotten every loop
    int sec=newtime/CLOCKS_PER_SEC; //seconds are difference between old and new times / CLOCKS_PER_SEC
    int min=sec/60;
    int txtW,txtH;
    char text[16];
    sprintf(text,"%02d : %02d",min,sec%60); //show mins and secs in typical shape
    TTF_Font *font=TTF_OpenFont("comicsans.ttf",28);
    SDL_Colour black={0,0,0,255};
    SDL_Surface *msg= TTF_RenderText_Blended(font,text,black);
    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(texture,0,0,&txtW,&txtH);
    SDL_Rect txtrect={WINDOW_WIDTH/2-txtW/2,2*TTF_FontLineSkip(font),txtW,txtH};
    SDL_RenderCopy(renderer,texture,0,&txtrect);
    SDL_DestroyTexture(texture);
}

#endif