#ifndef UNDO2X2_H
#define UNDO2X2_H
#include "gameShow2x2.h"

//edge box undo function
void boxUndo2x2(gameState2x2 *game2x2,int i,int j){
    if(game2x2->box[i][j].val==4){ //if box was filled
        game2x2->player--;
        if((game2x2->player-1)%2==0){ //if previous player was red decrease score
            game2x2->playerRed.score--;
        }
        else{ //if previous player was blue decrease score
            game2x2->playerBlue.score--;
        }
    }
    game2x2->box[i][j].val--;//dec value of box
}

//non-edge box undo function
void boxUndo2_2x2(gameState2x2 *game2x2,int i,int j,int k,int l){
    if(game2x2->box[i][j].val==4 && game2x2->box[k][l].val==4){ //if both boxes was filled
        game2x2->player--;
        if((game2x2->player-1)%2==0){ //if previous player was red decrease score by 2
            game2x2->playerRed.score-=2;
        }
        else{//if previous player was blue decrease score by 2 
            game2x2->playerBlue.score-=2;
        }
    }

    else if(game2x2->box[i][j].val==4){//if one box was filled
        game2x2->player--;
        if((game2x2->player-1)%2==0){
            game2x2->playerRed.score--;
        }
        else{
            game2x2->playerBlue.score--;
        }
    }

    else if(game2x2->box[k][l].val==4){//if other box was filled
        game2x2->player--;
        if((game2x2->player-1)%2==0){
            game2x2->playerRed.score--;
        }
        else{
            game2x2->playerBlue.score--;
        }
    }

    game2x2->box[i][j].val--; //decrease value of both boxes
    game2x2->box[k][l].val--;

    if(game2x2->box[i][j].val!=4){ //reset box
        game2x2->box[i][j].red=0;
        game2x2->box[i][j].blue=0;
    }

    if(game2x2->box[k][l].val!=4){ //reset box
        game2x2->box[k][l].red=0;
        game2x2->box[k][l].blue=0;
    }
}

//undo edge vertical line
void vLineUndo2x2(gameState2x2 *game2x2,int box1_X,int box1_Y){
    game2x2->A[game2x2->turn].type--;
    game2x2->vLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].val--; //reset line
    game2x2->vLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].red=0;
    game2x2->vLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].blue=0;
    boxUndo2x2(game2x2,box1_X,box1_Y); //undo adjacent box
}

//undo non-edge vertical line
void vLineUndo2_2x2(gameState2x2 *game2x2,int box1_X,int box1_Y,int box2_X,int box2_Y){
    game2x2->A[game2x2->turn].type--;
    game2x2->vLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].val--;//reset line
    game2x2->vLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].red=0;
    game2x2->vLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].blue=0;
    boxUndo2_2x2(game2x2,box1_X,box1_Y,box2_X,box2_Y);//undo adjacent boxes
}

//undo edge horizontal line
void hLineUndo2x2(gameState2x2 *game2x2,int box1_X,int box1_Y){
    game2x2->A[game2x2->turn].type--;//reset line
    game2x2->hLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].val--;
    game2x2->hLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].red=0;
    game2x2->hLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].blue=0;
    boxUndo2x2(game2x2,box1_X,box1_Y);//undo adjacent box
}

//undo non-edge horizontal line
void hLineUndo2_2x2(gameState2x2 *game2x2,int box1_X,int box1_Y,int box2_X,int box2_Y){
    game2x2->A[game2x2->turn].type--;//reset line
    game2x2->hLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].val--;
    game2x2->hLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].red=0;
    game2x2->hLine[game2x2->A[game2x2->turn].x][game2x2->A[game2x2->turn].y].blue=0;
    boxUndo2_2x2(game2x2,box1_X,box1_Y,box2_X,box2_Y);//undo adjacent boxes
}

#endif