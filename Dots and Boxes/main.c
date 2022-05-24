#include "input5x5.h"
#include "input2x2.h"
#include "newGameScreen.h"
#include "showMainMenu.h"
#include "defines.h"
#include "load.h"
#include "nameGet.h"

int main(int argc, char* argv[]){
    //load both leaderboards
    LoadLeaderboardEasy();
    LoadLeaderboardExpert();
    int done=0;
    //initialize window and renderer
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_TIMER);
    TTF_Init();
    window=SDL_CreateWindow("Dots and Boxes",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,0);
    renderer= SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    //main game loop
    while(!done){
        if(state==EASY){
            done=doLoop2x2(window,&game2x2);
            doRender2x2(renderer,&game2x2);
        }
        if(state==NEWGAME){
            doLoopNewGame(window);
            doRenderNewGame(renderer);
        }
        if(state==EXPERT){
            done=doLoop5x5(window,&game5x5);
            doRender5x5(renderer,&game5x5);
        }
        if(state==MAINMENU){
            //reset 2x2
            sprintf(game2x2.playerRed.name,"");
            sprintf(game2x2.playerBlue.name,"");
            sprintf(game5x5.playerRed.name,"");
            sprintf(game5x5.playerBlue.name,"");
            game2x2.player=0;
            game2x2.turn=-1;
            game2x2.playerRed.score=0;
            game2x2.playerBlue.score=0;
            for(int i=0;i<2;i++){
                for(int j=0;j<2;j++){
                    if(game2x2.box[i][j].val!=0){
                        game2x2.box[i][j].val=0;
                        game2x2.box[i][j].red=0;
                        game2x2.box[i][j].blue=0;
                    }
                }
            }
            for(int i=0;i<2;i++){
                for(int j=0;j<3;j++){
                    if(game2x2.vLine[i][j].val!=0){
                        game2x2.vLine[i][j].val=0;
                        game2x2.vLine[i][j].red=0;
                        game2x2.vLine[i][j].blue=0;
                    }
                }
            }
            for(int i=0;i<3;i++){
                for(int j=0;j<2;j++){
                    if(game2x2.hLine[i][j].val!=0){
                        game2x2.hLine[i][j].val=0;
                        game2x2.hLine[i][j].red=0;
                        game2x2.hLine[i][j].blue=0;
                    }
                }
            }
            //reset 5x5
            game5x5.player=0;
            game5x5.turn=-1;
            game5x5.playerRed.score=0;
            game5x5.playerBlue.score=0;
            for(int i=0;i<5;i++){
                for(int j=0;j<5;j++){
                    if(game5x5.box[i][j].val!=0){
                        game5x5.box[i][j].val=0;
                        game5x5.box[i][j].red=0;
                        game5x5.box[i][j].blue=0;
                    }
                }
            }
            for(int i=0;i<5;i++){
                for(int j=0;j<6;j++){
                    if(game5x5.vLine[i][j].val!=0){
                        game5x5.vLine[i][j].val=0;
                        game5x5.vLine[i][j].red=0;
                        game5x5.vLine[i][j].blue=0;
                    }
                }
            }
            for(int i=0;i<6;i++){
                for(int j=0;j<5;j++){
                    if(game5x5.hLine[i][j].val!=0){
                        game5x5.hLine[i][j].val=0;
                        game5x5.hLine[i][j].red=0;
                        game5x5.hLine[i][j].blue=0;
                    }
                }
            }
            
            done=doLoopMainMenu(window);
            doRenderMainMenu(renderer);
        }
        if(state==LEADERBOARD){
            done=doLoopLeaderboard(window);
            doRenderLeaderboard(renderer);
        }
        if(state==EASYLEADERBOARD){
            done=doLoopLeaderboardE(window);
            showLeaderboardEasy(renderer);
        }
        if(state==EXPERTLEADERBOARD){
            done=doLoopLeaderboardE(window);
            showLeaderboardExpert(renderer);
        }
        if(state==LOADGAME){
            done=doLoopLoad(window,&game2x2,&game5x5);
            doRenderLoad(renderer);
        }
        if(state==SAVES2X2){
            done=doLoopSave2x2(window,&game2x2);
            doRenderSave(renderer,"Save 1","Save 2");
        }
        if(state==SAVES5X5){
            done=doLoopSave5x5(window,&game5x5);
            doRenderSave(renderer,"Save 3","Save 4");
        }
        if(state==CHOOSEVS){
            done=doLoopChooseVS(window);
            doRenderChooseVS(renderer);
        }
        if(state==GETNAME2x2){
            static int player=0;
            done=doLoopgetName2x2(window,&game2x2,&player);
            doRendergetName2x2(renderer,&game2x2,player);
        }
        if(state==GETNAME5X5){
            static int player=0;
            done=doLoopgetName5x5(window,&game5x5,&player);
            doRendergetName5x5(renderer,&game5x5,player);
        }
        if(state==GETNAME2X2VSAI){
            sprintf(game2x2.playerBlue.name,"blueBoi");
            done=doLoopgetName2x2_2(window,&game2x2);
            doRendergetName2x2_2(renderer,&game2x2);
        }
        if(state==GETNAME5X5VSAI){
            sprintf(game5x5.playerBlue.name,"blueBoi");
            done=doLoopgetName5x5_2(window,&game5x5);
            doRendergetName5x5_2(renderer,&game5x5);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}