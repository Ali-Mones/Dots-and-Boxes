#ifndef SAVE_H
#define SAVE_H
#include "includes.h"
#include "defines.h"
#include "structs.h"
#include "showMainMenu.h"

//save 2x2 grid and its info
void save2x2(gameState2x2 *game2x2,char saveplace[32]){
    FILE *saveptr;
    saveptr=fopen(saveplace,"w");
    for(int i=0;i<2;i++){ //save vertical lines
        for(int j=0;j<3;j++){
            fprintf(saveptr,"%d ",game2x2->vLine[i][j].val);//value
            fprintf(saveptr,"%d ",game2x2->vLine[i][j].red); //if it's red or blue
            fprintf(saveptr,"%d\n",game2x2->vLine[i][j].blue);
        }
    }

    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){ //save horizontal lines
            fprintf(saveptr,"%d ",game2x2->hLine[i][j].val); //value
            fprintf(saveptr,"%d ",game2x2->hLine[i][j].red);//if it's red or blue
            fprintf(saveptr,"%d\n",game2x2->hLine[i][j].blue);
        }
    }

    for(int i=0;i<2;i++){ //save boxes
        for(int j=0;j<2;j++){
            fprintf(saveptr,"%d ",game2x2->box[i][j].val); //value
            fprintf(saveptr,"%d ",game2x2->box[i][j].red); //if it's red or blue
            fprintf(saveptr,"%d\n",game2x2->box[i][j].blue);
        }
    }

    for(int i=0;i<12;i++){
        fprintf(saveptr,"%d ",game2x2->A[i].type); //save game array for undo and redo
        fprintf(saveptr,"%d ",game2x2->A[i].x);
        fprintf(saveptr,"%d\n",game2x2->A[i].y);
    }
    
    fprintf(saveptr,"%s\n",game2x2->playerRed.name); //save red and blue info
    fprintf(saveptr,"%d\n",game2x2->playerRed.score);
    fprintf(saveptr,"%s\n",game2x2->playerBlue.name);
    fprintf(saveptr,"%d\n",game2x2->playerBlue.score);
    fprintf(saveptr,"%d\n",game2x2->player);
    fprintf(saveptr,"%d\n",game2x2->turn);
    fprintf(saveptr,"%d\n",ai); //if it's against ai or not
    fclose(saveptr);
}

void save5x5(gameState5x5 *game5x5,char saveplace[32]){
    FILE *saveptr;
    saveptr=fopen(saveplace,"w");
    for(int i=0;i<5;i++){ //save vertical lines
        for(int j=0;j<6;j++){
            fprintf(saveptr,"%d ",game5x5->vLine[i][j].val);//value
            fprintf(saveptr,"%d ",game5x5->vLine[i][j].red); //if it's red or blue
            fprintf(saveptr,"%d\n",game5x5->vLine[i][j].blue);
        }
    }

    for(int i=0;i<6;i++){ //save horizontal lines
        for(int j=0;j<5;j++){
            fprintf(saveptr,"%d ",game5x5->hLine[i][j].val); //value
            fprintf(saveptr,"%d ",game5x5->hLine[i][j].red); //if it's red or blue
            fprintf(saveptr,"%d\n",game5x5->hLine[i][j].blue);
        }
    }

    for(int i=0;i<5;i++){ //save boxes
        for(int j=0;j<5;j++){
            fprintf(saveptr,"%d ",game5x5->box[i][j].val); //value
            fprintf(saveptr,"%d ",game5x5->box[i][j].red); //if it's red or blue
            fprintf(saveptr,"%d\n",game5x5->box[i][j].blue);
        }
    }

    for(int i=0;i<60;i++){
        fprintf(saveptr,"%d ",game5x5->A[i].type); //save game array for undo and redo
        fprintf(saveptr,"%d ",game5x5->A[i].x);
        fprintf(saveptr,"%d\n",game5x5->A[i].y);
    }
    
    fprintf(saveptr,"%s\n",game5x5->playerRed.name); //save red and blue info
    fprintf(saveptr,"%d\n",game5x5->playerRed.score);
    fprintf(saveptr,"%s\n",game5x5->playerBlue.name);
    fprintf(saveptr,"%d\n",game5x5->playerBlue.score);
    fprintf(saveptr,"%d\n",game5x5->player);
    fprintf(saveptr,"%d\n",game5x5->turn);
    fprintf(saveptr,"%d\n",ai); //if it's against ai or not
    fclose(saveptr);
}

//show save screen
void doRenderSave(SDL_Renderer *renderer,char save1[8],char save2[8]){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rect1={0,WINDOW_HEIGHT/2-5,WINDOW_WIDTH,10};
    SDL_RenderFillRect(renderer,&rect1);
    menuText(renderer,save1,WINDOW_WIDTH/2,WINDOW_HEIGHT/4,255,0);
    menuText(renderer,save2,WINDOW_WIDTH/2,WINDOW_HEIGHT*3/4,0,255);
    SDL_RenderPresent(renderer);
}

//main loop for 2x2 saves
int doLoopSave2x2(SDL_Window *window,gameState2x2 *game2x2){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.y>0 && event.button.y<WINDOW_HEIGHT/2-5){
                    save2x2(game2x2,"save1.bin");
                    state=EASY;
                }
                else if(event.button.y>WINDOW_HEIGHT/2+5 && event.button.y<WINDOW_HEIGHT){
                    save2x2(game2x2,"save2.bin");
                    state=EASY;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE: //return to game
                        state=EASY;
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

//main loop for 5x5 saves
int doLoopSave5x5(SDL_Window *window,gameState5x5 *game5x5){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.y>0 && event.button.y<WINDOW_HEIGHT/2-5){
                    save5x5(game5x5,"save3.bin");
                    state=EXPERT;
                }
                else if(event.button.y>WINDOW_HEIGHT/2+5 && event.button.y<WINDOW_HEIGHT){
                    save5x5(game5x5,"save4.bin");
                    state=EXPERT;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE: //return to game
                        state=EXPERT;
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