#ifndef AI_H
#define AI_H
#include "includes.h"
#include "defines.h"
#include "structs.h"
#include "gameLogic2x2.h"
#include "gameLogic5x5.h"

//main loop for choosing vs screen
int doLoopChooseVS(SDL_Window *window){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.y>0 && event.button.y<WINDOW_HEIGHT/2-5){
                    ai=0;
                    state=NEWGAME;
                }
                else if(event.button.y>WINDOW_HEIGHT/2+5 && event.button.y<WINDOW_HEIGHT){
                    ai=1;
                    state=NEWGAME;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE: //return to difficulty selection screen
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

//show choose vs screen
void doRenderChooseVS(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rect1={0,WINDOW_HEIGHT/2-5,WINDOW_WIDTH,10};
    SDL_RenderFillRect(renderer,&rect1);
    menuText(renderer,"VS Player",WINDOW_WIDTH/2,WINDOW_HEIGHT/4,255,0);
    menuText(renderer,"VS AI",WINDOW_WIDTH/2,WINDOW_HEIGHT*3/4,0,255);
    SDL_RenderPresent(renderer);
}

//EasyMode random AI function
void AI2x2(gameState2x2 *game2x2){
    while(game2x2->player%2==1){ //while it's blue player's turn
        validVertical vArray2x2[6]; //array of valid vertical lines
        int m=0;
        int sizeV=0;
        for(int i=0;i<2;i++){ //make array every loop
            for(int j=0;j<3;j++){
                if(game2x2->vLine[i][j].val==0){
                    vArray2x2[m].x=i;
                    vArray2x2[m++].y=j;
                    sizeV++;
                }
                    
            }
        }

        validHorizontal hArray2x2[6]; //array of valid horizontal lines
        int k=0;
        int sizeH=0;
        for(int i=0;i<3;i++){ //make array every loop
            for(int j=0;j<2;j++){
                if(game2x2->hLine[i][j].val==0){
                    hArray2x2[k].x=i;
                    hArray2x2[k++].y=j;
                    sizeH++;
                }
                    
            }
        }

        srand(time(0));
        if(sizeV!=0 && sizeH!=0){ //both horizontal and vertical lines are valid
            int base=rand()%2; //choose horizontal or vertical line
            if(base==0){
                int x=rand()%sizeV;
                if(vArray2x2[x].y==0){
                    vLineColouring2x2(game2x2,vArray2x2[x].x,vArray2x2[x].y,vArray2x2[x].x,vArray2x2[x].y);
                }
                else if(vArray2x2[x].y==2){
                    vLineColouring2x2(game2x2,vArray2x2[x].x,vArray2x2[x].y,vArray2x2[x].x,vArray2x2[x].y-1);
                }
                else{
                    vLineColouring2_2x2(game2x2,vArray2x2[x].x,vArray2x2[x].y,vArray2x2[x].x,vArray2x2[x].y,vArray2x2[x].x,vArray2x2[x].y-1);
                }
            }
            else if(base==1){
                int x=rand()%sizeH; 
                if(hArray2x2[x].x==0){
                    hLineColouring2x2(game2x2,hArray2x2[x].x,hArray2x2[x].y,hArray2x2[x].x,hArray2x2[x].y);
                }
                else if(hArray2x2[x].x==2){
                    hLineColouring2x2(game2x2,hArray2x2[x].x,hArray2x2[x].y,hArray2x2[x].x-1,hArray2x2[x].y);
                }
                else{
                    hLineColouring2_2x2(game2x2,hArray2x2[x].x,hArray2x2[x].y,hArray2x2[x].x,hArray2x2[x].y,hArray2x2[x].x-1,hArray2x2[x].y);
                }
                
            }
        }
        else if(sizeV==0 && sizeH==0){ //both line types aren't valid (ai win)
            break;
        }
        else if(sizeV==0){ //only horizontal lines are valid
            int x=rand()%sizeH;
            if(hArray2x2[x].x==0){
                hLineColouring2x2(game2x2,hArray2x2[x].x,hArray2x2[x].y,hArray2x2[x].x,hArray2x2[x].y);
            }
            else if(hArray2x2[x].x==2){
                hLineColouring2x2(game2x2,hArray2x2[x].x,hArray2x2[x].y,hArray2x2[x].x-1,hArray2x2[x].y);
            }
            else{
                hLineColouring2_2x2(game2x2,hArray2x2[x].x,hArray2x2[x].y,hArray2x2[x].x,hArray2x2[x].y,hArray2x2[x].x-1,hArray2x2[x].y);
            }
        }
        else if(sizeH==0){ //only vertical lines are valid
            int x=rand()%sizeV;
            if(vArray2x2[x].y==0){
                vLineColouring2x2(game2x2,vArray2x2[x].x,vArray2x2[x].y,vArray2x2[x].x,vArray2x2[x].y);
            }
            else if(vArray2x2[x].y==2){
                vLineColouring2x2(game2x2,vArray2x2[x].x,vArray2x2[x].y,vArray2x2[x].x,vArray2x2[x].y-1);
            }
            else{
                vLineColouring2_2x2(game2x2,vArray2x2[x].x,vArray2x2[x].y,vArray2x2[x].x,vArray2x2[x].y,vArray2x2[x].x,vArray2x2[x].y-1);
            }
        }
    }
}

//ExpertMode random AI function
void AI5x5(gameState5x5 *game5x5){
    while(game5x5->player%2==1){ //while it's blue player's turn
        validVertical vArray5x5[30]; //array of valid vertical lines
        int m=0;
        int sizeV=0;
        for(int i=0;i<5;i++){ //make array every loop
            for(int j=0;j<6;j++){
                if(game5x5->vLine[i][j].val==0){
                    vArray5x5[m].x=i;
                    vArray5x5[m++].y=j;
                    sizeV++;
                }
                    
            }
        }

        validHorizontal hArray5x5[30]; //array of valid horizontal lines
        int k=0;
        int sizeH=0;
        for(int i=0;i<6;i++){ //make array every loop
            for(int j=0;j<5;j++){
                if(game5x5->hLine[i][j].val==0){
                    hArray5x5[k].x=i;
                    hArray5x5[k++].y=j;
                    sizeH++;
                }
                    
            }
        }

        srand(time(0));
        if(sizeV!=0 && sizeH!=0){ //both horizontal and vertical lines are valid
            int base=rand()%2; //choose horizontal or vertical line
            if(base==0){
                int x=rand()%sizeV;
                if(vArray5x5[x].y==0){
                    vLineColouring5x5(game5x5,vArray5x5[x].x,vArray5x5[x].y,vArray5x5[x].x,vArray5x5[x].y);
                }
                else if(vArray5x5[x].y==5){
                    vLineColouring5x5(game5x5,vArray5x5[x].x,vArray5x5[x].y,vArray5x5[x].x,vArray5x5[x].y-1);
                }
                else{
                    vLineColouring2_5x5(game5x5,vArray5x5[x].x,vArray5x5[x].y,vArray5x5[x].x,vArray5x5[x].y,vArray5x5[x].x,vArray5x5[x].y-1);
                }
            }
            else if(base==1){
                int x=rand()%sizeH; 
                if(hArray5x5[x].x==0){
                    hLineColouring5x5(game5x5,hArray5x5[x].x,hArray5x5[x].y,hArray5x5[x].x,hArray5x5[x].y);
                }
                else if(hArray5x5[x].x==5){
                    hLineColouring5x5(game5x5,hArray5x5[x].x,hArray5x5[x].y,hArray5x5[x].x-1,hArray5x5[x].y);
                }
                else{
                    hLineColouring2_5x5(game5x5,hArray5x5[x].x,hArray5x5[x].y,hArray5x5[x].x,hArray5x5[x].y,hArray5x5[x].x-1,hArray5x5[x].y);
                }
                
            }
        }
        else if(sizeV==0 && sizeH==0){ //both line types aren't valid (ai win)
            break;
        }
        else if(sizeV==0){ //only horizontal lines are valid
            int x=rand()%sizeH;
            if(hArray5x5[x].x==0){
                hLineColouring5x5(game5x5,hArray5x5[x].x,hArray5x5[x].y,hArray5x5[x].x,hArray5x5[x].y);
            }
            else if(hArray5x5[x].x==5){
                hLineColouring5x5(game5x5,hArray5x5[x].x,hArray5x5[x].y,hArray5x5[x].x-1,hArray5x5[x].y);
            }
            else{
                hLineColouring2_5x5(game5x5,hArray5x5[x].x,hArray5x5[x].y,hArray5x5[x].x,hArray5x5[x].y,hArray5x5[x].x-1,hArray5x5[x].y);
            }
        }
        else if(sizeH==0){ //only vertical lines are valid
            int x=rand()%sizeV;
            if(vArray5x5[x].y==0){
                vLineColouring5x5(game5x5,vArray5x5[x].x,vArray5x5[x].y,vArray5x5[x].x,vArray5x5[x].y);
            }
            else if(vArray5x5[x].y==5){
                vLineColouring5x5(game5x5,vArray5x5[x].x,vArray5x5[x].y,vArray5x5[x].x,vArray5x5[x].y-1);
            }
            else{
                vLineColouring2_5x5(game5x5,vArray5x5[x].x,vArray5x5[x].y,vArray5x5[x].x,vArray5x5[x].y,vArray5x5[x].x,vArray5x5[x].y-1);
            }
        }
    }
}

#endif