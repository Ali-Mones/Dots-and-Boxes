#ifndef NEWGAMESCREEN_H
#define NEWGAMESCREEN_H
#include "defines.h"
#include "includes.h"
#include "showMainMenu.h"

//show diffculty selection screen
void doRenderNewGame(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rect1={0,WINDOW_HEIGHT/2-5,WINDOW_WIDTH,10};
    SDL_RenderFillRect(renderer,&rect1);
    menuText(renderer,"Easy Mode",WINDOW_WIDTH/2,WINDOW_HEIGHT/4,255,0);
    menuText(renderer,"Expert Mode",WINDOW_WIDTH/2,WINDOW_HEIGHT*3/4,0,255);
    SDL_RenderPresent(renderer);
}

//main loop for difficulty selection screen
int doLoopNewGame(SDL_Window *window){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.y>0 && event.button.y<WINDOW_HEIGHT/2-5){
                    if(ai==0){
                        state=GETNAME2x2;
                    }
                    else{
                        state=GETNAME2X2VSAI;
                    }
                }
                else if(event.button.y>WINDOW_HEIGHT/2+5 && event.button.y<WINDOW_HEIGHT){
                    if(ai==0){
                        state=GETNAME5X5;
                    }
                    else{
                        state=GETNAME5X5VSAI;
                    }
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        state=MAINMENU;
                        break;
                }
                break;
            case SDL_QUIT:
                done=1;
                break;
            case SDL_WINDOWEVENT_CLOSE:
                if(window){
                    SDL_DestroyWindow(window);
                    done=1;
                }
                break;
        }
    }

    return done;
}


#endif