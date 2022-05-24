#ifndef GAMESHOW5x5_H
#define GAMESHOW5x5_H
#include "includes.h"
#include "structs.h"
#include "defines.h"
#include "leaderboard.h"
#include "timer.h"

Dots dot5x5[6][6]; //dots array

gameState5x5 game5x5={.turn=-1}; //set turns to -1

//show red player's info
void showRedInfo5x5(gameState5x5 *game5x5,SDL_Renderer *renderer){
    char redScore[1];
    int txtW,txtH;
    TTF_Font *font= TTF_OpenFont("comicsans.ttf",32);
    SDL_Color red={255,0,0,255};
    SDL_Surface *msg;
    SDL_Texture *text;
    msg=TTF_RenderText_Blended(font,game5x5->playerRed.name,red);
    text=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(text,0,0,&txtW,&txtH);
    SDL_Rect txtRect={10,0,txtW,txtH};
    SDL_RenderCopy(renderer,text,0,&txtRect); //show name
    SDL_DestroyTexture(text);
    sprintf(redScore,"score: %d",game5x5->playerRed.score);
    msg=TTF_RenderText_Blended(font,redScore,red);
    text=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(text,0,0,&txtW,&txtH);
    SDL_Rect txtRect2={10,TTF_FontLineSkip(font),txtW,txtH};
    SDL_RenderCopy(renderer,text,0,&txtRect2); //show score
}

//show blue player's info
void showBlueInfo5x5(gameState5x5 *game5x5,SDL_Renderer *renderer){
    int txtW,txtH;
    char blueScore[1];
    TTF_Font *font= TTF_OpenFont("comicsans.ttf",32);
    SDL_Color blue={0,0,255,255};
    SDL_Surface *msg;
    SDL_Texture *text;
    msg=TTF_RenderText_Blended(font,game5x5->playerBlue.name,blue);
    text=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(text,0,0,&txtW,&txtH);
    SDL_Rect txtRect={WINDOW_WIDTH-txtW-10,0,txtW,txtH};
    SDL_RenderCopy(renderer,text,0,&txtRect); //show name
    SDL_DestroyTexture(text);
    sprintf(blueScore,"score: %d",game5x5->playerBlue.score);
    msg=TTF_RenderText_Blended(font,blueScore,blue);
    text=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(text,0,0,&txtW,&txtH);
    SDL_Rect txtRect2={WINDOW_WIDTH-txtW-10,TTF_FontLineSkip(font),txtW,txtH};
    SDL_RenderCopy(renderer,text,0,&txtRect2); //show score
}

//show moves left and whose turn it is
void showExtra5x5(gameState5x5 *game5x5,SDL_Renderer *renderer){
    char movesLeft[128];
    char whoseTurn[128];
    int txt1W,txt1H,txt2W,txt2H;
    SDL_Colour black={0,0,0,255};
    SDL_Colour red={255,0,0,255};
    SDL_Colour blue={0,0,255,255};
    sprintf(movesLeft,"%d moves left",60-1-game5x5->turn);
    TTF_Font *font=TTF_OpenFont("comicsans.ttf",28);
    SDL_Surface *msg=TTF_RenderText_Blended(font,movesLeft,black);
    SDL_Texture *txt=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_QueryTexture(txt,0,0,&txt1W,&txt1H);
    SDL_Rect txtRect1={WINDOW_WIDTH/2-txt1W/2,0,txt1W,txt1H};
    SDL_RenderCopy(renderer,txt,0,&txtRect1); //show moves left
    SDL_FreeSurface(msg);
    SDL_DestroyTexture(txt);
    //set turns to player's colour
    if(game5x5->player%2==0){
        sprintf(whoseTurn,"%s's turn",game5x5->playerRed.name);
        msg=TTF_RenderText_Blended(font,whoseTurn,red); 
    }
    else{
        sprintf(whoseTurn,"%s's turn",game5x5->playerBlue.name);
        msg=TTF_RenderText_Blended(font,whoseTurn,blue);
    }
    txt=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_QueryTexture(txt,0,0,&txt2W,&txt2H);
    SDL_Rect txtRect2={WINDOW_WIDTH/2-txt2W/2,TTF_FontLineSkip(font),txt2W,txt2H};
    SDL_RenderCopy(renderer,txt,0,&txtRect2); //show whose turn it is
}

//shown on win
void showWinner5x5(gameState5x5 *game5x5,SDL_Renderer *renderer,int player){
    int txtW,txtH,txt2W,txt2H;
    TTF_Font *font=TTF_OpenFont("comicsans.ttf",64);
    SDL_Colour white={255,255,255,255};
    SDL_Colour colour;
    char score[128];
    char name[128];
    //set text to player's colour 
    if(player==-1){ 
        colour.r=255;
        colour.g=0;
        colour.b=255;
        colour.a=255;
        sprintf(name,"TIE");
        sprintf(score,"%d EACH",game5x5->playerRed.score); //if tied set to grey
    }
    if(player==0){
        colour.r=255;
        colour.a=255;
        colour.b=0;
        colour.g=0;
        sprintf(name,"%s WINS",game5x5->playerRed.name);
        sprintf(score,"SCORE: %d",game5x5->playerRed.score);
        addRedToLeaderboardExpert(game5x5);
    }
    else if(player==1){
        colour.b=255;
        colour.a=255;
        colour.r=0;
        colour.g=0;
        sprintf(name,"%s WINS",game5x5->playerBlue.name);
        sprintf(score,"SCORE: %d",game5x5->playerBlue.score);
        addBlueToLeaderboardExpert(game5x5);
    }
    SDL_Surface *msg=TTF_RenderText_Blended(font,name,colour);
    SDL_Texture *txt=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(txt,0,0,&txtW,&txtH);
    SDL_Rect txtRect={WINDOW_WIDTH/2-txtW/2,WINDOW_HEIGHT/2-txtH,txtW,txtH};
    SDL_RenderCopy(renderer,txt,0,&txtRect); //show winner's name
    SDL_DestroyTexture(txt);
    msg=TTF_RenderText_Shaded(font,score,colour,white);
    txt=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(txt,0,0,&txt2W,&txt2H);
    SDL_Rect txtRect2={WINDOW_WIDTH/2-txt2W/2,WINDOW_HEIGHT/2,txt2W,txt2H};
    SDL_RenderCopy(renderer,txt,0,&txtRect2); //show winner's score
    SDL_DestroyTexture(txt);
}

//main rendering of 5x5 game
void doRender5x5(SDL_Renderer *renderer,gameState5x5 *game5x5){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    for (int j=0;j<6;j++){ //show dots
        for (int i=0;i<6;i++){
            dot5x5[i][j].x=WINDOW_WIDTH*(i+1.5)/8;
            dot5x5[i][j].y=WINDOW_HEIGHT*(j+1.5)/8;
            SDL_Rect rect={dot5x5[i][j].x-15,dot5x5[i][j].y-15,30,30};
            SDL_RenderFillRect(renderer,&rect);
        }
    }
    for(int i=0;i<6;i++){//show horizontal lines made
        for(int j=0;j<5;j++){
            if(game5x5->hLine[i][j].val==1){
                SDL_SetRenderDrawColor(renderer,game5x5->hLine[i][j].red,0,game5x5->hLine[i][j].blue,255);
                SDL_Rect rect={dot5x5[j][i].x+15,dot5x5[j][i].y-15,WINDOW_WIDTH/8-30,30};
                SDL_RenderFillRect(renderer,&rect);
            }
        }
    }
    for(int i=0;i<5;i++){//show vertical lines made
        for(int j=0;j<6;j++){
            if(game5x5->vLine[i][j].val==1){
                SDL_SetRenderDrawColor(renderer,game5x5->vLine[i][j].red,0,game5x5->vLine[i][j].blue,255);
                SDL_Rect rect={dot5x5[j][i].x-15,dot5x5[j][i].y+15,30,WINDOW_HEIGHT/8-30};
                SDL_RenderFillRect(renderer,&rect);
            }
        }
    }
    for(int i=0;i<5;i++){ //show boxes filled
        for(int j=0;j<5;j++){
            if(game5x5->box[i][j].val==4){
                SDL_SetRenderDrawColor(renderer,game5x5->box[i][j].red,0,game5x5->box[i][j].blue,255);
                SDL_Rect rect={dot5x5[j][i].x+15,dot5x5[j][i].y+15,WINDOW_WIDTH/8-30,WINDOW_HEIGHT/8-30};
                SDL_RenderFillRect(renderer,&rect);
            }
        }
    }


    SDL_SetRenderDrawColor(renderer,0,0,0,255);//show basic shape of game
    SDL_Rect rect1={dot5x5[0][0].x-15,dot5x5[0][0].y-15,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect2={dot5x5[0][0].x-15,dot5x5[0][0].y+12,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect3={dot5x5[0][1].x-15,dot5x5[0][1].y-15,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect4={dot5x5[0][1].x-15,dot5x5[0][1].y+12,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect5={dot5x5[0][2].x-15,dot5x5[0][2].y-15,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect6={dot5x5[0][2].x-15,dot5x5[0][2].y+12,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect7={dot5x5[0][3].x-15,dot5x5[0][3].y-15,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect8={dot5x5[0][3].x-15,dot5x5[0][3].y+12,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect9={dot5x5[0][4].x-15,dot5x5[0][4].y-15,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect10={dot5x5[0][4].x-15,dot5x5[0][4].y+12,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect11={dot5x5[0][5].x-15,dot5x5[0][5].y-15,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect12={dot5x5[0][5].x-15,dot5x5[0][5].y+12,WINDOW_WIDTH*5/8+30,3};
    SDL_Rect rect13={dot5x5[0][0].x-15,dot5x5[0][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    SDL_Rect rect14={dot5x5[0][0].x+12,dot5x5[0][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    SDL_Rect rect15={dot5x5[1][0].x-15,dot5x5[1][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    SDL_Rect rect16={dot5x5[1][0].x+12,dot5x5[1][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    SDL_Rect rect17={dot5x5[2][0].x-15,dot5x5[2][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    SDL_Rect rect18={dot5x5[2][0].x+12,dot5x5[2][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    SDL_Rect rect19={dot5x5[3][0].x-15,dot5x5[3][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    SDL_Rect rect20={dot5x5[3][0].x+12,dot5x5[3][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    SDL_Rect rect21={dot5x5[4][0].x-15,dot5x5[4][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    SDL_Rect rect22={dot5x5[4][0].x+12,dot5x5[4][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    SDL_Rect rect23={dot5x5[5][0].x-15,dot5x5[5][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    SDL_Rect rect24={dot5x5[5][0].x+12,dot5x5[5][0].y-15,3,WINDOW_HEIGHT*5/8+30};
    
    SDL_RenderFillRect(renderer,&rect1);
    SDL_RenderFillRect(renderer,&rect2);
    SDL_RenderFillRect(renderer,&rect3);
    SDL_RenderFillRect(renderer,&rect4);
    SDL_RenderFillRect(renderer,&rect5);
    SDL_RenderFillRect(renderer,&rect6);
    SDL_RenderFillRect(renderer,&rect7);
    SDL_RenderFillRect(renderer,&rect8);
    SDL_RenderFillRect(renderer,&rect9);
    SDL_RenderFillRect(renderer,&rect10);
    SDL_RenderFillRect(renderer,&rect11);
    SDL_RenderFillRect(renderer,&rect12);
    SDL_RenderFillRect(renderer,&rect13);
    SDL_RenderFillRect(renderer,&rect14);
    SDL_RenderFillRect(renderer,&rect15);
    SDL_RenderFillRect(renderer,&rect16);
    SDL_RenderFillRect(renderer,&rect17);
    SDL_RenderFillRect(renderer,&rect18);
    SDL_RenderFillRect(renderer,&rect19);
    SDL_RenderFillRect(renderer,&rect20);
    SDL_RenderFillRect(renderer,&rect21);
    SDL_RenderFillRect(renderer,&rect22);
    SDL_RenderFillRect(renderer,&rect23);
    SDL_RenderFillRect(renderer,&rect24);
    //show extra info
    showTime(renderer);
    menuBottomText(renderer,"Press S to save",5,WINDOW_HEIGHT,20);
    menuBottomText(renderer,"Press Esc to go to main menu",5,WINDOW_HEIGHT-60,20);
    menuBottomText(renderer,"Use mouse to choose line",5,WINDOW_HEIGHT-80,20);
    menuBottomText(renderer,"Press Z to undo",5,WINDOW_HEIGHT-40,20);
    menuBottomText(renderer,"Press Y to redo",5,WINDOW_HEIGHT-20,20);
    showRedInfo5x5(game5x5,renderer);
    showBlueInfo5x5(game5x5,renderer);
    showExtra5x5(game5x5,renderer);
    //win condition
    if(game5x5->turn==59){
        int player=-1;
        if(game5x5->playerRed.score>game5x5->playerBlue.score){
            player=0;
        }
        else{
            player=1;
        }
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_Rect winnerRect={WINDOW_WIDTH/2-WINDOW_WIDTH*5/16,WINDOW_HEIGHT/2-WINDOW_HEIGHT*5/16,WINDOW_WIDTH*5/8,WINDOW_HEIGHT*5/8}; //white bg box
        SDL_RenderFillRect(renderer,&winnerRect);
        showWinner5x5(game5x5,renderer,player);
    }
    SDL_RenderPresent(renderer); //show everything 
}

#endif