#ifndef GAMELOGIC2X2_H
#define GAMELOGIC2X2_H
#include "gameShow2x2.h"

//edge box colouring
void boxColouring2x2(gameState2x2 *game2x2,int i,int j){
    game2x2->box[i][j].val++; //add one for every side
    if(game2x2->box[i][j].val==4){ //when val = 4 colour it with last player played
        if(game2x2->player%2==0){
            game2x2->box[i][j].red=255;
            game2x2->playerRed.score++; //add red score
        }
        else{
            game2x2->box[i][j].blue=255;
            game2x2->playerBlue.score++; //add blue score
        }
        game2x2->player++; //player gets to play again
    }
}

void boxColouring2_2x2(gameState2x2 *game2x2, int i,int j,int k,int l){ //non-edge boxes colouring
    game2x2->box[i][j].val++; //add one to both boxes affected by side chosen
    game2x2->box[k][l].val++; //add one to both boxes affected by side chosen

    if(game2x2->box[i][j].val==4 && game2x2->box[k][l].val==4){ //both boxes filled
        if(game2x2->player%2==0){
            game2x2->box[i][j].red=255;
            game2x2->box[k][l].red=255;
            game2x2->playerRed.score++; //red gets 2 points
            game2x2->playerRed.score++;
        }
        else{
            game2x2->box[k][l].blue=255;
            game2x2->box[i][j].blue=255;
            game2x2->playerBlue.score++; //blue gets 2 points
            game2x2->playerBlue.score++;
        }
        game2x2->player++;
    }

    //only one box filled
    else if(game2x2->box[i][j].val==4){ 
        if(game2x2->player%2==0){
            game2x2->box[i][j].red=255;
            game2x2->playerRed.score++;
        }
        else{
            game2x2->box[i][j].blue=255;
            game2x2->playerBlue.score++;
        }
        game2x2->player++;
    }

    else if(game2x2->box[k][l].val==4){
        if(game2x2->player%2==0){
            game2x2->box[k][l].red=255;
            game2x2->playerRed.score++;
        }
        else{
            game2x2->box[k][l].blue=255;
            game2x2->playerBlue.score++;
        }
        game2x2->player++;
    }
}

//colouring edge vertical lines
void vLineColouring2x2(gameState2x2 *game2x2,int vLineX,int vLineY,int box1_X,int box1_Y){
    if(game2x2->vLine[vLineX][vLineY].val!=1){
        game2x2->turn++;
        game2x2->vLine[vLineX][vLineY].val=1; //make value one to be drawn
        game2x2->A[game2x2->turn].type=vertical; //record the turn made in turns array
        game2x2->A[game2x2->turn].x=vLineX;
        game2x2->A[game2x2->turn].y=vLineY;
        if(game2x2->player%2==0){
            game2x2->vLine[vLineX][vLineY].red=255;
        }
        else{
            game2x2->vLine[vLineX][vLineY].blue=255;
        }
    boxColouring2x2(game2x2,box1_X,box1_Y); //affect adjacent box
    game2x2->player++; //other player plays
    }
}

//colouring non-edge vertical lines
void vLineColouring2_2x2(gameState2x2 *game2x2,int vLineX,int vLineY,int box1_X,int box1_Y,int box2_X,int box2_Y){
    if(game2x2->vLine[vLineX][vLineY].val!=1){
        game2x2->turn++;
        game2x2->vLine[vLineX][vLineY].val=1;
        game2x2->A[game2x2->turn].type=vertical;
        game2x2->A[game2x2->turn].x=vLineX;
        game2x2->A[game2x2->turn].y=vLineY;
        if(game2x2->player%2==0){
            game2x2->vLine[vLineX][vLineY].red=255;
        }
        else{
            game2x2->vLine[vLineX][vLineY].blue=255;
        }
    boxColouring2_2x2(game2x2,box1_X,box1_Y,box2_X,box2_Y); //affect both adjacent boxes
    game2x2->player++;
    }
}

//same as edge vertical lines
void hLineColouring2x2(gameState2x2 *game2x2,int hLineX,int hLineY,int box1_X,int box1_Y){
    if(game2x2->hLine[hLineX][hLineY].val!=1){
        game2x2->turn++;
        game2x2->hLine[hLineX][hLineY].val=1;
        game2x2->A[game2x2->turn].type=horizontal;
        game2x2->A[game2x2->turn].x=hLineX;
        game2x2->A[game2x2->turn].y=hLineY;
        if(game2x2->player%2==0){
            game2x2->hLine[hLineX][hLineY].red=255;
        }
        else{
            game2x2->hLine[hLineX][hLineY].blue=255;
        }
    boxColouring2x2(game2x2,box1_X,box1_Y);
    game2x2->player++;
    }
}

//same as non-edge vertical lines
void hLineColouring2_2x2(gameState2x2 *game2x2,int hLineX,int hLineY,int box1_X,int box1_Y,int box2_X,int box2_Y){
    if(game2x2->hLine[hLineX][hLineY].val!=1){
        game2x2->turn++;
        game2x2->hLine[hLineX][hLineY].val=1;
        game2x2->A[game2x2->turn].type=horizontal;
        game2x2->A[game2x2->turn].x=hLineX;
        game2x2->A[game2x2->turn].y=hLineY;
        if(game2x2->player%2==0){
            game2x2->hLine[hLineX][hLineY].red=255;
        }
        else{
            game2x2->hLine[hLineX][hLineY].blue=255;
        }
    boxColouring2_2x2(game2x2,box1_X,box1_Y,box2_X,box2_Y);
    game2x2->player++;
    }
}

#endif