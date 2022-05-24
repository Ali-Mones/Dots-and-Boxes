#ifndef INPUT2x2_H
#define INPUT2x2_H
#include "gameShow2x2.h"
#include "gameLogic2x2.h"
#include "undo2x2.h"
#include "save.h"
#include "ai.h"

//main loop for 2x2 game
int doLoop2x2(SDL_Window *window,gameState2x2 *game2x2){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_s:
                        state=SAVES2X2; //savemenu
                        break;
                    case SDLK_y: //redo function
                        if(game2x2->A[game2x2->turn+1].type!=0){
                            if(game2x2->A[game2x2->turn+1].type==vertical-1){ //check if vertical line
                                if(game2x2->A[game2x2->turn+1].y==0){ //left edge vertical line
                                    vLineColouring2x2(game2x2,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y);
                                }
                                else if(game2x2->A[game2x2->turn+1].y==2){//right edge vertical line
                                    vLineColouring2x2(game2x2,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y-1);
                                }
                                else{//non-edge vertical line
                                    vLineColouring2_2x2(game2x2,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y-1);
                                }
                            }
                            else if(game2x2->A[game2x2->turn+1].type==horizontal-1){ //check if horizontal line
                                if(game2x2->A[game2x2->turn+1].x==0){//top edge horizontal line
                                        hLineColouring2x2(game2x2,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y);
                                    }
                                    else if(game2x2->A[game2x2->turn+1].x==2){//bottom edge horizontal line
                                        hLineColouring2x2(game2x2,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y,game2x2->A[game2x2->turn+1].x-1,game2x2->A[game2x2->turn+1].y);
                                    }
                                    else{//non-edge horizontal line
                                        hLineColouring2_2x2(game2x2,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y,game2x2->A[game2x2->turn+1].x,game2x2->A[game2x2->turn+1].y,game2x2->A[game2x2->turn+1].x-1,game2x2->A[game2x2->turn+1].y);
                                    }
                            }
                        }
                        break;
                    case SDLK_z: //undo function
                        if (game2x2->turn!=-1){
                            if(game2x2->A[game2x2->turn].type==vertical){ //check if vertical line
                                if(game2x2->A[game2x2->turn].y==0){ //left edge vertical line
                                    vLineUndo2x2(game2x2,game2x2->A[game2x2->turn].x,game2x2->A[game2x2->turn].y);
                                }
                                else if(game2x2->A[game2x2->turn].y==2){//right edge vertical line
                                    vLineUndo2x2(game2x2,game2x2->A[game2x2->turn].x,game2x2->A[game2x2->turn].y-1);
                                }
                                else{//non-edge vertical line
                                    vLineUndo2_2x2(game2x2,game2x2->A[game2x2->turn].x,game2x2->A[game2x2->turn].y,game2x2->A[game2x2->turn].x,game2x2->A[game2x2->turn].y-1);
                                }
                            }
                            else if(game2x2->A[game2x2->turn].type==horizontal){ //check if horizontal line
                                if(game2x2->A[game2x2->turn].x==0){ //top edge horizontal line
                                        hLineUndo2x2(game2x2,game2x2->A[game2x2->turn].x,game2x2->A[game2x2->turn].y);
                                    }
                                    else if(game2x2->A[game2x2->turn].x==2){ //bottom edge horizontal line
                                        hLineUndo2x2(game2x2,game2x2->A[game2x2->turn].x-1,game2x2->A[game2x2->turn].y);
                                    }
                                    else{ //non-edge horizontal line
                                        hLineUndo2_2x2(game2x2,game2x2->A[game2x2->turn].x,game2x2->A[game2x2->turn].y,game2x2->A[game2x2->turn].x-1,game2x2->A[game2x2->turn].y);
                                    }
                            }
                            game2x2->turn--; //revert to previous turn
                            game2x2->player--; //revert to previous player
                        }
                        break;
                    case SDLK_ESCAPE: //go to mainmenu
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
            case SDL_MOUSEBUTTONDOWN: //check if mouse is pressed and where
                if(event.button.button == SDL_BUTTON_LEFT){
                    for(int i=0;i<2;i++){//vertical lines
                        for(int j=0;j<3;j++){
                            if(event.button.x<dot2x2[j][i].x+15 && event.button.x>dot2x2[j][i].x-15 && event.button.y>dot2x2[j][i].y+15 && event.button.y<dot2x2[j][i].y+WINDOW_HEIGHT/4-15){
                                if(j==0){
                                    vLineColouring2x2(game2x2,i,j,i,j); //left edge
                                    if(ai==1){ //check to see if vs ai
                                        AI2x2(game2x2); //ai plays
                                    }
                                }
                                else if(j==2){
                                    vLineColouring2x2(game2x2,i,j,i,j-1); //right edge
                                    if(ai==1){ //check to see if vs ai
                                        AI2x2(game2x2); //ai plays
                                    }
                                }
                                else{
                                    vLineColouring2_2x2(game2x2,i,j,i,j,i,j-1); //non-edge
                                    if(ai==1){ //check to see if vs ai
                                        AI2x2(game2x2); //ai plays
                                    }
                                }
                                for(int i=game2x2->turn+1;i<12;i++){ //reset all redo when valid move is made
                                    game2x2->A[i].type=0;
                                    game2x2->A[i].x=0;
                                    game2x2->A[i].y=0;
                                }
                            }
                        }
                    }
                    for(int i=0;i<3;i++){ //horizontal lines
                        for(int j=0;j<2;j++){
                            if(event.button.x>dot2x2[j][i].x+15 && event.button.x<dot2x2[j][i].x+15+WINDOW_WIDTH/4-30 && event.button.y>dot2x2[j][i].y-15 && event.button.y<dot2x2[j][i].y+15){
                                if(i==0){
                                    hLineColouring2x2(game2x2,i,j,i,j); //top edge
                                    if(ai==1){ //check to see if vs ai
                                        AI2x2(game2x2); //ai plays
                                    }
                                }
                                else if(i==2){
                                    hLineColouring2x2(game2x2,i,j,i-1,j); //bottom edge
                                    if(ai==1){ //check to see if vs ai
                                        AI2x2(game2x2); //ai plays
                                    }
                                }
                                else{
                                    hLineColouring2_2x2(game2x2,i,j,i,j,i-1,j); //non-edge
                                    if(ai==1){ //check to see if vs ai
                                        AI2x2(game2x2); //ai plays
                                    }
                                }
                                for(int i=game2x2->turn+1;i<12;i++){ //reset all redo when valid move is made
                                    game2x2->A[i].type=0;
                                    game2x2->A[i].x=0;
                                    game2x2->A[i].y=0;
                                }
                            }
                        }
                    }
                }
            
            break;
        }
    }
    return done;
}

#endif