#ifndef INPUT5X5_H
#define INPUT5X5_H
#include "gameShow5x5.h"
#include "gameLogic5x5.h"
#include "undo5x5.h"
#include "ai.h"

//main loop for 5x5 game
int doLoop5x5(SDL_Window *window,gameState5x5 *game5x5){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_s:
                        state=SAVES5X5;
                        break;
                    case SDLK_y: //redo function
                        if(game5x5->A[game5x5->turn+1].type!=0){
                            if(game5x5->A[game5x5->turn+1].type==vertical-1){ //check if vertical line
                                if(game5x5->A[game5x5->turn+1].y==0){ //left edge vertical line
                                    vLineColouring5x5(game5x5,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y);
                                }
                                else if(game5x5->A[game5x5->turn+1].y==5){//right edge vertical line
                                    vLineColouring5x5(game5x5,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y-1);
                                }
                                else{//non-edge vertical line
                                    vLineColouring2_5x5(game5x5,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y-1);
                                }
                            }
                            else if(game5x5->A[game5x5->turn+1].type==horizontal-1){ //check if horizontal line
                                if(game5x5->A[game5x5->turn+1].x==0){//top edge horizontal line
                                        hLineColouring5x5(game5x5,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y);
                                    }
                                    else if(game5x5->A[game5x5->turn+1].x==5){//bottom edge horizontal line
                                        hLineColouring5x5(game5x5,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y,game5x5->A[game5x5->turn+1].x-1,game5x5->A[game5x5->turn+1].y);
                                    }
                                    else{//non-edge horizontal line
                                        hLineColouring2_5x5(game5x5,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y,game5x5->A[game5x5->turn+1].x,game5x5->A[game5x5->turn+1].y,game5x5->A[game5x5->turn+1].x-1,game5x5->A[game5x5->turn+1].y);
                                    }
                            }
                        }
                        break;
                    case SDLK_z: //undo function
                        if (game5x5->turn!=-1){
                            if(game5x5->A[game5x5->turn].type==vertical){ //check if vertical line
                                if(game5x5->A[game5x5->turn].y==0){ //left edge vertical line
                                    vLineUndo5x5(game5x5,game5x5->A[game5x5->turn].x,game5x5->A[game5x5->turn].y);
                                }
                                else if(game5x5->A[game5x5->turn].y==5){//right edge vertical line
                                    vLineUndo5x5(game5x5,game5x5->A[game5x5->turn].x,game5x5->A[game5x5->turn].y-1);
                                }
                                else{//non-edge vertical line
                                    vLineUndo2_5x5(game5x5,game5x5->A[game5x5->turn].x,game5x5->A[game5x5->turn].y,game5x5->A[game5x5->turn].x,game5x5->A[game5x5->turn].y-1);
                                }
                            }
                            else if(game5x5->A[game5x5->turn].type==horizontal){ //check if horizontal line
                                if(game5x5->A[game5x5->turn].x==0){ //top edge horizontal line
                                        hLineUndo5x5(game5x5,game5x5->A[game5x5->turn].x,game5x5->A[game5x5->turn].y);
                                    }
                                    else if(game5x5->A[game5x5->turn].x==5){ //bottom edge horizontal line
                                        hLineUndo5x5(game5x5,game5x5->A[game5x5->turn].x-1,game5x5->A[game5x5->turn].y);
                                    }
                                    else{ //non-edge horizontal line
                                        hLineUndo2_5x5(game5x5,game5x5->A[game5x5->turn].x,game5x5->A[game5x5->turn].y,game5x5->A[game5x5->turn].x-1,game5x5->A[game5x5->turn].y);
                                    }
                            }
                            game5x5->turn--; //revert to previous turn
                            game5x5->player--; //revert to previous player
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
                    for(int i=0;i<5;i++){//vertical lines
                        for(int j=0;j<6;j++){
                            if(event.button.x<dot5x5[j][i].x+15 && event.button.x>dot5x5[j][i].x-15 && event.button.y>dot5x5[j][i].y+15 && event.button.y<dot5x5[j][i].y+WINDOW_HEIGHT/8-15){
                                if(j==0){
                                    vLineColouring5x5(game5x5,i,j,i,j); //left edge
                                    if(ai==1){ //check to see if vs ai
                                        AI5x5(game5x5); //ai plays
                                    }
                                }
                                else if(j==5){
                                    vLineColouring5x5(game5x5,i,j,i,j-1); //right edge
                                    if(ai==1){ //check to see if vs ai
                                        AI5x5(game5x5); //ai plays
                                    }
                                }
                                else{
                                    vLineColouring2_5x5(game5x5,i,j,i,j,i,j-1); //non-edge
                                    if(ai==1){ //check to see if vs ai
                                        AI5x5(game5x5); //ai plays
                                    }
                                }
                                for(int i=game5x5->turn+1;i<60;i++){ //reset all redo when valid move is made
                                    game5x5->A[i].type=0;
                                    game5x5->A[i].x=0;
                                    game5x5->A[i].y=0;
                                }
                            }
                        }
                    }
                    for(int i=0;i<6;i++){ //horizontal lines
                        for(int j=0;j<5;j++){
                            if(event.button.x>dot5x5[j][i].x+15 && event.button.x<dot5x5[j][i].x+15+WINDOW_WIDTH/8-30 && event.button.y>dot5x5[j][i].y-15 && event.button.y<dot5x5[j][i].y+15){
                                if(i==0){
                                    hLineColouring5x5(game5x5,i,j,i,j); //top edge
                                    if(ai==1){ //check to see if vs ai
                                        AI5x5(game5x5); //ai plays
                                    }
                                }
                                else if(i==5){
                                    hLineColouring5x5(game5x5,i,j,i-1,j); //bottom edge
                                    if(ai==1){ //check to see if vs ai
                                        AI5x5(game5x5); //ai plays
                                    }
                                }
                                else{
                                    hLineColouring2_5x5(game5x5,i,j,i,j,i-1,j); //non-edge
                                    if(ai==1){ //check to see if vs ai
                                        AI5x5(game5x5); //ai plays
                                    }
                                }
                                for(int i=game5x5->turn+1;i<60;i++){
                                    game5x5->A[i].type=0;
                                    game5x5->A[i].x=0;
                                    game5x5->A[i].y=0;
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