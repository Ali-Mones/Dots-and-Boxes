#ifndef LOAD_H
#define LOAD_H
#include "includes.h"
#include "defines.h"
#include "structs.h"
#include "save.h"
#include "showMainMenu.h"

//load easy mode games from bin files
void load2x2(gameState2x2 *game2x2,char saveplace[32]){
    oldTime=clock();
    FILE *loadptr;
    loadptr=fopen(saveplace,"r");
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            fscanf(loadptr,"%d %d %d\n",&game2x2->vLine[i][j].val,&game2x2->vLine[i][j].red,&game2x2->vLine[i][j].blue);
        }
    }

    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            fscanf(loadptr,"%d %d %d\n",&game2x2->hLine[i][j].val,&game2x2->hLine[i][j].red,&game2x2->hLine[i][j].blue);
        }
    }

    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            fscanf(loadptr,"%d %d %d\n",&game2x2->box[i][j].val,&game2x2->box[i][j].red,&game2x2->box[i][j].blue);
        }
    }

    for(int i=0;i<12;i++){
        fscanf(loadptr,"%d %d %d\n",&game2x2->A[i].type,&game2x2->A[i].x,&game2x2->A[i].y);
    }

    fscanf(loadptr,"%s\n",game2x2->playerRed.name);
    fscanf(loadptr,"%d\n",&game2x2->playerRed.score);
    fscanf(loadptr,"%s\n",game2x2->playerBlue.name);
    fscanf(loadptr,"%d\n",&game2x2->playerBlue.score);
    fscanf(loadptr,"%d\n",&game2x2->player);
    fscanf(loadptr,"%d\n",&game2x2->turn);
    fscanf(loadptr,"%d\n",&ai);
    fclose(loadptr);
}

//load expert mode games from bin files
void load5x5(gameState5x5 *game5x5,char saveplace[32]){
    oldTime=clock();
    FILE *loadptr;
    loadptr=fopen(saveplace,"r");
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            fscanf(loadptr,"%d %d %d\n",&game5x5->vLine[i][j].val,&game5x5->vLine[i][j].red,&game5x5->vLine[i][j].blue);
        }
    }

    for(int i=0;i<6;i++){
        for(int j=0;j<5;j++){
            fscanf(loadptr,"%d %d %d\n",&game5x5->hLine[i][j].val,&game5x5->hLine[i][j].red,&game5x5->hLine[i][j].blue);
        }
    }

    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            fscanf(loadptr,"%d %d %d\n",&game5x5->box[i][j].val,&game5x5->box[i][j].red,&game5x5->box[i][j].blue);
        }
    }

    for(int i=0;i<60;i++){
        fscanf(loadptr,"%d %d %d\n",&game5x5->A[i].type,&game5x5->A[i].x,&game5x5->A[i].y);
    }

    fscanf(loadptr,"%s\n",game5x5->playerRed.name);
    fscanf(loadptr,"%d\n",&game5x5->playerRed.score);
    fscanf(loadptr,"%s\n",game5x5->playerBlue.name);
    fscanf(loadptr,"%d\n",&game5x5->playerBlue.score);
    fscanf(loadptr,"%d\n",&game5x5->player);
    fscanf(loadptr,"%d\n",&game5x5->turn);
    fscanf(loadptr,"%d\n",&ai);
    fclose(loadptr);
}

void doRenderLoad(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    //general shape
    SDL_Rect rect1={0,WINDOW_HEIGHT/4-5,WINDOW_WIDTH,10};
    SDL_Rect rect2={0,WINDOW_HEIGHT*2/4-5,WINDOW_WIDTH,10};
    SDL_Rect rect3={0,WINDOW_HEIGHT*3/4-5,WINDOW_WIDTH,10};
    SDL_RenderFillRect(renderer,&rect1);
    SDL_RenderFillRect(renderer,&rect2);
    SDL_RenderFillRect(renderer,&rect3);
    //show text
    menuText(renderer,"Save 1 - EasyMode",WINDOW_WIDTH/2,WINDOW_HEIGHT/8,255,0);
    menuText(renderer,"Save 2 - EasyMode",WINDOW_WIDTH/2,WINDOW_HEIGHT*3/8,0,255);
    menuText(renderer,"Save 3 - ExpertMode",WINDOW_WIDTH/2,WINDOW_HEIGHT*5/8,255,0);
    menuText(renderer,"Save 4 - ExpertMode",WINDOW_WIDTH/2,WINDOW_HEIGHT*7/8,0,255);
    SDL_RenderPresent(renderer);
}

int doLoopLoad(SDL_Window *window,gameState2x2 *game2x2,gameState5x5 *game5x5){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.y>0 && event.button.y<WINDOW_HEIGHT/4-5){
                    load2x2(game2x2,"save1.bin");
                    state=EASY;
                }
                else if(event.button.y>WINDOW_HEIGHT/4+5 && event.button.y<WINDOW_HEIGHT*2/4-5){
                    load2x2(game2x2,"save2.bin");
                    state=EASY;
                }
                else if(event.button.y>WINDOW_HEIGHT*2/4+5 && event.button.y<WINDOW_HEIGHT*3/4-5){
                    load5x5(game5x5,"save3.bin");
                    state=EXPERT;
                }
                else if(event.button.y>WINDOW_HEIGHT*3/4+5 && event.button.y<WINDOW_HEIGHT){
                    load5x5(game5x5,"save4.bin");
                    state=EXPERT;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE: //return to menu
                        state=MAINMENU;
                        break;
                }
                break;
            case SDL_QUIT: //exit game using X
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