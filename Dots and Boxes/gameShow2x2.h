#ifndef GAMESHOW2X2_H
#define GAMESHOW2X2_H
#include "includes.h"
#include "structs.h"
#include "defines.h"
#include "leaderboard.h"
#include "timer.h"

Dots dot2x2[3][3]; //dots array

gameState2x2 game2x2={.turn=-1}; //set turns to -1

//show red player's info
void showRedInfo2x2(gameState2x2 *game2x2,SDL_Renderer *renderer){
    char redScore[1];
    int txtW,txtH;
    TTF_Font *font= TTF_OpenFont("comicsans.ttf",32);
    SDL_Color red={255,0,0,255};
    SDL_Surface *msg;
    SDL_Texture *text;
    msg=TTF_RenderText_Blended(font,game2x2->playerRed.name,red);
    text=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(text,0,0,&txtW,&txtH);
    SDL_Rect txtRect={10,0,txtW,txtH};
    SDL_RenderCopy(renderer,text,0,&txtRect); //show name
    SDL_DestroyTexture(text);
    sprintf(redScore,"score: %d",game2x2->playerRed.score);
    msg=TTF_RenderText_Blended(font,redScore,red);
    text=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(text,0,0,&txtW,&txtH);
    SDL_Rect txtRect2={10,TTF_FontLineSkip(font),txtW,txtH};
    SDL_RenderCopy(renderer,text,0,&txtRect2); //show score
}

//show blue player's info
void showBlueInfo2x2(gameState2x2 *game2x2,SDL_Renderer *renderer){
    int txtW,txtH;
    char blueScore[1];
    TTF_Font *font= TTF_OpenFont("comicsans.ttf",32);
    SDL_Color blue={0,0,255,255};
    SDL_Surface *msg;
    SDL_Texture *text;
    msg=TTF_RenderText_Blended(font,game2x2->playerBlue.name,blue);
    text=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(text,0,0,&txtW,&txtH);
    SDL_Rect txtRect={WINDOW_WIDTH-txtW-10,0,txtW,txtH};
    SDL_RenderCopy(renderer,text,0,&txtRect); //show name
    SDL_DestroyTexture(text);
    sprintf(blueScore,"score: %d",game2x2->playerBlue.score);
    msg=TTF_RenderText_Blended(font,blueScore,blue);
    text=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(text,0,0,&txtW,&txtH);
    SDL_Rect txtRect2={WINDOW_WIDTH-txtW-10,TTF_FontLineSkip(font),txtW,txtH};
    SDL_RenderCopy(renderer,text,0,&txtRect2); //show score
}

//show moves left and whose turn it is
void showExtra2x2(gameState2x2 *game2x2,SDL_Renderer *renderer){
    char movesLeft[128];
    char whoseTurn[128];
    int txt1W,txt1H,txt2W,txt2H;
    SDL_Colour black={0,0,0,255};
    SDL_Colour red={255,0,0,255};
    SDL_Colour blue={0,0,255,255};
    sprintf(movesLeft,"%d moves left",12-1-game2x2->turn);
    TTF_Font *font=TTF_OpenFont("comicsans.ttf",28);
    SDL_Surface *msg=TTF_RenderText_Blended(font,movesLeft,black);
    SDL_Texture *txt=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_QueryTexture(txt,0,0,&txt1W,&txt1H);
    SDL_Rect txtRect1={WINDOW_WIDTH/2-txt1W/2,0,txt1W,txt1H};
    SDL_RenderCopy(renderer,txt,0,&txtRect1); //show moves left
    SDL_FreeSurface(msg);
    SDL_DestroyTexture(txt);
    //set turns to player's colour
    if(game2x2->player%2==0){
        sprintf(whoseTurn,"%s's turn",game2x2->playerRed.name);
        msg=TTF_RenderText_Blended(font,whoseTurn,red); 
    }
    else{
        sprintf(whoseTurn,"%s's turn",game2x2->playerBlue.name);
        msg=TTF_RenderText_Blended(font,whoseTurn,blue);
    }
    txt=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_QueryTexture(txt,0,0,&txt2W,&txt2H);
    SDL_Rect txtRect2={WINDOW_WIDTH/2-txt2W/2,TTF_FontLineSkip(font),txt2W,txt2H};
    SDL_RenderCopy(renderer,txt,0,&txtRect2); //show whose turn it is
    
}

//shown on win
void showWinner2x2(gameState2x2 *game2x2,SDL_Renderer *renderer,int player){
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
        sprintf(score,"%d EACH",game2x2->playerRed.score); //if tied set to grey
    }
    if(player==0){
        colour.r=255;
        colour.a=255;
        colour.b=0;
        colour.g=0;
        sprintf(name,"%s WINS",game2x2->playerRed.name);
        sprintf(score,"SCORE: %d",game2x2->playerRed.score);
        addRedToLeaderboardEasy(game2x2);
    }
    else if(player==1){
        colour.b=255;
        colour.a=255;
        colour.r=0;
        colour.g=0;
        sprintf(name,"%s WINS",game2x2->playerBlue.name);
        sprintf(score,"SCORE: %d",game2x2->playerBlue.score);
        addBlueToLeaderboardEasy(game2x2);
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

//main rendering of 2x2 game
void doRender2x2(SDL_Renderer *renderer,gameState2x2 *game2x2){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    for (int j=0;j<3;j++){ //show dots
        for (int i=0;i<3;i++){
            dot2x2[i][j].x=WINDOW_WIDTH*(i+1)/4;
            dot2x2[i][j].y=WINDOW_HEIGHT*(j+1)/4;
            SDL_Rect rect={dot2x2[i][j].x-15,dot2x2[i][j].y-15,30,30};
            SDL_RenderFillRect(renderer,&rect);
        }
    }
    for(int i=0;i<3;i++){//show horizontal lines made
        for(int j=0;j<2;j++){
            if(game2x2->hLine[i][j].val==1){
                SDL_SetRenderDrawColor(renderer,game2x2->hLine[i][j].red,0,game2x2->hLine[i][j].blue,255);
                SDL_Rect rect={dot2x2[j][i].x+15,dot2x2[j][i].y-15,WINDOW_WIDTH/4-30,30};
                SDL_RenderFillRect(renderer,&rect);
            }
        }
    }
    for(int i=0;i<2;i++){//show vertical lines made
        for(int j=0;j<3;j++){
            if(game2x2->vLine[i][j].val==1){
                SDL_SetRenderDrawColor(renderer,game2x2->vLine[i][j].red,0,game2x2->vLine[i][j].blue,255);
                SDL_Rect rect={dot2x2[j][i].x-15,dot2x2[j][i].y+15,30,WINDOW_HEIGHT/4-30};
                SDL_RenderFillRect(renderer,&rect);
            }
        }
    }
    for(int i=0;i<2;i++){ //show boxes filled
        for(int j=0;j<2;j++){
            if(game2x2->box[i][j].val==4){
                SDL_SetRenderDrawColor(renderer,game2x2->box[i][j].red,0,game2x2->box[i][j].blue,255);
                SDL_Rect rect={dot2x2[j][i].x+15,dot2x2[j][i].y+15,WINDOW_WIDTH/4-30,WINDOW_HEIGHT/4-30};
                SDL_RenderFillRect(renderer,&rect);
            }
        }
    }

    //show basic shape of game
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rect1={dot2x2[0][0].x-15,dot2x2[0][0].y-15,WINDOW_WIDTH/2+30,3};
    SDL_Rect rect2={dot2x2[0][0].x-15,dot2x2[0][0].y+12,WINDOW_WIDTH/2+30,3};
    SDL_Rect rect3={dot2x2[0][1].x-15,dot2x2[0][1].y-15,WINDOW_WIDTH/2+30,3};
    SDL_Rect rect4={dot2x2[0][1].x-15,dot2x2[0][1].y+12,WINDOW_WIDTH/2+30,3};
    SDL_Rect rect5={dot2x2[0][2].x-15,dot2x2[0][2].y-15,WINDOW_WIDTH/2+30,3};
    SDL_Rect rect6={dot2x2[0][2].x-15,dot2x2[0][2].y+12,WINDOW_WIDTH/2+30,3};
    SDL_Rect rect7={dot2x2[0][0].x-15,dot2x2[0][0].y-15,3,WINDOW_HEIGHT/2+30};
    SDL_Rect rect8={dot2x2[0][0].x+12,dot2x2[0][0].y-15,3,WINDOW_HEIGHT/2+30};
    SDL_Rect rect9={dot2x2[1][0].x-15,dot2x2[1][0].y-15,3,WINDOW_HEIGHT/2+30};
    SDL_Rect rect10={dot2x2[1][0].x+12,dot2x2[1][0].y-15,3,WINDOW_HEIGHT/2+30};
    SDL_Rect rect11={dot2x2[2][0].x-15,dot2x2[2][0].y-15,3,WINDOW_HEIGHT/2+30};
    SDL_Rect rect12={dot2x2[2][0].x+12,dot2x2[2][0].y-15,3,WINDOW_HEIGHT/2+30};
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
    //show extra info on screen
    showTime(renderer);
    menuBottomText(renderer,"Press S to save",5,WINDOW_HEIGHT,20);
    menuBottomText(renderer,"Press Esc to go to main menu",5,WINDOW_HEIGHT-60,20);
    menuBottomText(renderer,"Use mouse to choose line",5,WINDOW_HEIGHT-80,20);
    menuBottomText(renderer,"Press Z to undo",5,WINDOW_HEIGHT-40,20);
    menuBottomText(renderer,"Press Y to redo",5,WINDOW_HEIGHT-20,20);
    showRedInfo2x2(game2x2,renderer);
    showBlueInfo2x2(game2x2,renderer);
    showExtra2x2(game2x2,renderer);
    //win condition
    if(game2x2->turn==11){
        int player=-1;
        if(game2x2->playerRed.score>game2x2->playerBlue.score){
            player=0;
        }
        else if(game2x2->playerRed.score<game2x2->playerBlue.score){
            player=1;
        }
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_Rect winnerRect={WINDOW_WIDTH/2-WINDOW_WIDTH/4,WINDOW_HEIGHT/2-WINDOW_HEIGHT/4,WINDOW_WIDTH/2,WINDOW_HEIGHT/2}; //white bg box
        SDL_RenderFillRect(renderer,&winnerRect);
        showWinner2x2(game2x2,renderer,player);
    }
    SDL_RenderPresent(renderer); //show everything
}

#endif