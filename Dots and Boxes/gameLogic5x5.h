#ifndef GAMELOGIC5X5_H
#define GAMELOGIC5X5_H
#include "gameShow5x5.h"

//edge box colouring
void boxColouring5x5(gameState5x5 *game5x5,int i,int j){
    game5x5->box[i][j].val++; //add one for every side
    if(game5x5->box[i][j].val==4){ //when val = 4 colour it with last player played
        if(game5x5->player%2==0){
            game5x5->box[i][j].red=255;
            game5x5->playerRed.score++; //add red score
        }
        else{
            game5x5->box[i][j].blue=255;
            game5x5->playerBlue.score++; //add blue score
        }
        game5x5->player++; //player gets to play again
    }
}

void boxColouring2_5x5(gameState5x5 *game5x5, int i,int j,int k,int l){ //non-edge boxes colouring
    game5x5->box[i][j].val++; //add one to both boxes affected by side chosen
    game5x5->box[k][l].val++; //add one to both boxes affected by side chosen

    if(game5x5->box[i][j].val==4 && game5x5->box[k][l].val==4){ //both boxes filled
        if(game5x5->player%2==0){
            game5x5->box[i][j].red=255;
            game5x5->box[k][l].red=255;
            game5x5->playerRed.score++; //red gets 2 points
            game5x5->playerRed.score++;
        }
        else{
            game5x5->box[k][l].blue=255;
            game5x5->box[i][j].blue=255;
            game5x5->playerBlue.score++; //blue gets 2 points
            game5x5->playerBlue.score++;
        }
        game5x5->player++;
    }

    //only one box filled
    else if(game5x5->box[i][j].val==4){ 
        if(game5x5->player%2==0){
            game5x5->box[i][j].red=255;
            game5x5->playerRed.score++;
        }
        else{
            game5x5->box[i][j].blue=255;
            game5x5->playerBlue.score++;
        }
        game5x5->player++;
    }

    else if(game5x5->box[k][l].val==4){
        if(game5x5->player%2==0){
            game5x5->box[k][l].red=255;
            game5x5->playerRed.score++;
        }
        else{
            game5x5->box[k][l].blue=255;
            game5x5->playerBlue.score++;
        }
        game5x5->player++;
    }
}

//colouring edge vertical lines
void vLineColouring5x5(gameState5x5 *game5x5,int vLineX,int vLineY,int box1_X,int box1_Y){
    if(game5x5->vLine[vLineX][vLineY].val!=1){
        game5x5->turn++;
        game5x5->vLine[vLineX][vLineY].val=1; //make value one to be drawn
        game5x5->A[game5x5->turn].type=vertical; //record the turn made in turns array
        game5x5->A[game5x5->turn].x=vLineX;
        game5x5->A[game5x5->turn].y=vLineY;
        if(game5x5->player%2==0){
            game5x5->vLine[vLineX][vLineY].red=255;
        }
        else{
            game5x5->vLine[vLineX][vLineY].blue=255;
        }
    boxColouring5x5(game5x5,box1_X,box1_Y); //affect adjacent box
    game5x5->player++; //other player plays
    }
}

//colouring non-edge vertical lines
void vLineColouring2_5x5(gameState5x5 *game5x5,int vLineX,int vLineY,int box1_X,int box1_Y,int box2_X,int box2_Y){
    if(game5x5->vLine[vLineX][vLineY].val!=1){
        game5x5->turn++;
        game5x5->vLine[vLineX][vLineY].val=1;
        game5x5->A[game5x5->turn].type=vertical;
        game5x5->A[game5x5->turn].x=vLineX;
        game5x5->A[game5x5->turn].y=vLineY;
        if(game5x5->player%2==0){
            game5x5->vLine[vLineX][vLineY].red=255;
        }
        else{
            game5x5->vLine[vLineX][vLineY].blue=255;
        }
    boxColouring2_5x5(game5x5,box1_X,box1_Y,box2_X,box2_Y); //affect both adjacent boxes
    game5x5->player++;
    }
}

//same as edge vertical lines
void hLineColouring5x5(gameState5x5 *game5x5,int hLineX,int hLineY,int box1_X,int box1_Y){
    if(game5x5->hLine[hLineX][hLineY].val!=1){
        game5x5->turn++;
        game5x5->hLine[hLineX][hLineY].val=1;
        game5x5->A[game5x5->turn].type=horizontal;
        game5x5->A[game5x5->turn].x=hLineX;
        game5x5->A[game5x5->turn].y=hLineY;
        if(game5x5->player%2==0){
            game5x5->hLine[hLineX][hLineY].red=255;
        }
        else{
            game5x5->hLine[hLineX][hLineY].blue=255;
        }
    boxColouring5x5(game5x5,box1_X,box1_Y);
    game5x5->player++;
    }
}

//same as non-edge vertical lines
void hLineColouring2_5x5(gameState5x5 *game5x5,int hLineX,int hLineY,int box1_X,int box1_Y,int box2_X,int box2_Y){
    if(game5x5->hLine[hLineX][hLineY].val!=1){
        game5x5->turn++;
        game5x5->hLine[hLineX][hLineY].val=1;
        game5x5->A[game5x5->turn].type=horizontal;
        game5x5->A[game5x5->turn].x=hLineX;
        game5x5->A[game5x5->turn].y=hLineY;
        if(game5x5->player%2==0){
            game5x5->hLine[hLineX][hLineY].red=255;
        }
        else{
            game5x5->hLine[hLineX][hLineY].blue=255;
        }
    boxColouring2_5x5(game5x5,box1_X,box1_Y,box2_X,box2_Y);
    game5x5->player++;
    }
}

#endif