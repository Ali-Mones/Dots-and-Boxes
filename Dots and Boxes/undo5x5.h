#ifndef UNDO5X5_H
#define UNDO5X5_H
#include "gameShow5x5.h"

//edge box undo function
void boxUndo5x5(gameState5x5 *game5x5,int i,int j){
    if(game5x5->box[i][j].val==4){ //if box was filled
        game5x5->player--;
        if((game5x5->player-1)%2==0){ //if previous player was red decrease score
            game5x5->playerRed.score--;
        }
        else{ //if previous player was blue decrease score
            game5x5->playerBlue.score--;
        }
    }
    game5x5->box[i][j].val--;//dec value of box
}

//non-edge box undo function
void boxUndo2_5x5(gameState5x5 *game5x5,int i,int j,int k,int l){
    if(game5x5->box[i][j].val==4 && game5x5->box[k][l].val==4){ //if both boxes was filled
        game5x5->player--;
        if((game5x5->player-1)%2==0){ //if previous player was red decrease score by 2
            game5x5->playerRed.score-=2;
        }
        else{//if previous player was blue decrease score by 2 
            game5x5->playerBlue.score-=2;
        }
    }

    else if(game5x5->box[i][j].val==4){//if one box was filled
        game5x5->player--;
        if((game5x5->player-1)%2==0){
            game5x5->playerRed.score--;
        }
        else{
            game5x5->playerBlue.score--;
        }
    }

    else if(game5x5->box[k][l].val==4){//if other box was filled
        game5x5->player--;
        if((game5x5->player-1)%2==0){
            game5x5->playerRed.score--;
        }
        else{
            game5x5->playerBlue.score--;
        }
    }

    game5x5->box[i][j].val--; //decrease value of both boxes
    game5x5->box[k][l].val--;

    if(game5x5->box[i][j].val!=4){ //reset box
        game5x5->box[i][j].red=0;
        game5x5->box[i][j].blue=0;
    }

    if(game5x5->box[k][l].val!=4){ //reset box
        game5x5->box[k][l].red=0;
        game5x5->box[k][l].blue=0;
    }
}

//undo edge vertical line
void vLineUndo5x5(gameState5x5 *game5x5,int box1_X,int box1_Y){
    game5x5->A[game5x5->turn].type--;
    game5x5->vLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].val--; //reset line
    game5x5->vLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].red=0;
    game5x5->vLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].blue=0;
    boxUndo5x5(game5x5,box1_X,box1_Y); //undo adjacent box
}

//undo non-edge vertical line
void vLineUndo2_5x5(gameState5x5 *game5x5,int box1_X,int box1_Y,int box2_X,int box2_Y){
    game5x5->A[game5x5->turn].type--;
    game5x5->vLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].val--;//reset line
    game5x5->vLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].red=0;
    game5x5->vLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].blue=0;
    boxUndo2_5x5(game5x5,box1_X,box1_Y,box2_X,box2_Y);//undo adjacent boxes
}

//undo edge horizontal line
void hLineUndo5x5(gameState5x5 *game5x5,int box1_X,int box1_Y){
    game5x5->A[game5x5->turn].type--;//reset line
    game5x5->hLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].val--;
    game5x5->hLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].red=0;
    game5x5->hLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].blue=0;
    boxUndo5x5(game5x5,box1_X,box1_Y);//undo adjacent box
}

//undo non-edge horizontal line
void hLineUndo2_5x5(gameState5x5 *game5x5,int box1_X,int box1_Y,int box2_X,int box2_Y){
    game5x5->A[game5x5->turn].type--;//reset line
    game5x5->hLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].val--;
    game5x5->hLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].red=0;
    game5x5->hLine[game5x5->A[game5x5->turn].x][game5x5->A[game5x5->turn].y].blue=0;
    boxUndo2_5x5(game5x5,box1_X,box1_Y,box2_X,box2_Y);//undo adjacent boxes
}

#endif