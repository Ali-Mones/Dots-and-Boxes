#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "includes.h"
#include "defines.h"
#include "structs.h"
#include "showMainMenu.h"

//bubble sort EasyMode leaderboard array
void sortListEasy(){
    for(int i=0;i<256-1;i++){
        for(int j=0;j<256-i-1;j++){
            if(leaderboardEasy[j].score<leaderboardEasy[j+1].score){
                winners temp=leaderboardEasy[j];
                leaderboardEasy[j]=leaderboardEasy[j+1];
                leaderboardEasy[j+1]=temp;
            }
        }
    }
}

//add red winner to EasyMode leaderboard
void addRedToLeaderboardEasy(gameState2x2 *game2x2){
    int found=0;
    mainFile=fopen("leaderboardEasy.bin","w");
    //if already exists update it
    for(int i=0;i<256;i++){
        if(strcmp(leaderboardEasy[i].name,game2x2->playerRed.name)==0){
            found=1;
            if(leaderboardEasy[i].score<game2x2->playerRed.score){
                leaderboardEasy[i].score=game2x2->playerRed.score;
            }
        }
    }
    //if new add to end
    if(found==0){
        sprintf(leaderboardEasy[255].name,"%s",game2x2->playerRed.name);
        leaderboardEasy[255].score=game2x2->playerRed.score;
    }
    sortListEasy(); //sort leaderboard
    //print to txt file
    for(int i=0;i<256;i++){
        fprintf(mainFile,"EasyMode - %s with score: %d\n",leaderboardEasy[i].name,leaderboardEasy[i].score);
    }
    fclose(mainFile);
}

//add blue winner to EasyMode leaderboard
void addBlueToLeaderboardEasy(gameState2x2 *game2x2){
    int found=0;
    mainFile=fopen("leaderboardEasy.bin","w");
    //if already exists update it
    for(int i=0;i<256;i++){
        if(strcmp(leaderboardEasy[i].name,game2x2->playerBlue.name)==0){
            found=1;
            if(leaderboardEasy[i].score<game2x2->playerBlue.score){
                leaderboardEasy[i].score=game2x2->playerBlue.score;
            }
        }
    }
    //if new add to end
    if(found==0){
        sprintf(leaderboardEasy[255].name,"%s",game2x2->playerBlue.name);
        leaderboardEasy[255].score=game2x2->playerBlue.score;
    }
    //sort leaderboard
    sortListEasy();
    //print to txt file
    for(int i=0;i<256;i++){
        fprintf(mainFile,"EasyMode - %s with score: %d\n",leaderboardEasy[i].name,leaderboardEasy[i].score);
    }
    fclose(mainFile);
}

//loading EasyMode leaderboard from bin file
void LoadLeaderboardEasy(){
    FILE *ptr;
    ptr=fopen("leaderboardEasy.bin","r");
    //read every element
    for(int i=0;i<256;i++){
        fscanf(ptr,"EasyMode - %s with score: %d\n",leaderboardEasy[i].name,&leaderboardEasy[i].score);
    }
    fclose(ptr);
    //if name is empty make it NULL
    for(int i=0;i<256;i++){
        if(strcmp(leaderboardEasy[i].name,"")==0){
            sprintf(leaderboardEasy[i].name,"NULL");
        }
    }
}

//loading ExpertMode leaderboard from bin file
void LoadLeaderboardExpert(){
    FILE *ptr;
    ptr=fopen("leaderboardExpert.bin","r");
    //read every element
    for(int i=0;i<256;i++){
        fscanf(ptr,"ExpertMode - %s with score: %d\n",leaderboardExpert[i].name,&leaderboardExpert[i].score);
    }
    fclose(ptr);
    //if name is empty make it NULL
    for(int i=0;i<256;i++){
        if(strcmp(leaderboardExpert[i].name,"")==0){
            sprintf(leaderboardExpert[i].name,"NULL");
        }
    }
}

//bubble sort ExpertMode leaderboard array
void sortListExpert(){
    for(int i=0;i<256-1;i++){
        for(int j=0;j<256-i-1;j++){
            if(leaderboardExpert[j].score<leaderboardExpert[j+1].score){
                winners temp=leaderboardExpert[j];
                leaderboardExpert[j]=leaderboardExpert[j+1];
                leaderboardExpert[j+1]=temp;
            }
        }
    }
}

//same as EasyMode
void addRedToLeaderboardExpert(gameState5x5 *game5x5){
    int found=0;
    mainFile=fopen("leaderboardExpert.bin","w");
    for(int i=0;i<256;i++){
        if(strcmp(leaderboardExpert[i].name,game5x5->playerRed.name)==0){
            found=1;
            if(leaderboardExpert[i].score<game5x5->playerRed.score){
                leaderboardExpert[i].score=game5x5->playerRed.score;
            }
        }
    }
    if(found==0){
        sprintf(leaderboardExpert[255].name,"%s",game5x5->playerRed.name);
        leaderboardExpert[255].score=game5x5->playerRed.score;
    }
    sortListExpert();
    for(int i=0;i<256;i++){
        fprintf(mainFile,"ExpertMode - %s with score: %d\n",leaderboardExpert[i].name,leaderboardExpert[i].score);
    }
    fclose(mainFile);
}

//same as EasyMode
void addBlueToLeaderboardExpert(gameState5x5 *game5x5){
    int found=0;
    mainFile=fopen("leaderboardExpert.bin","w");
    for(int i=0;i<256;i++){
        if(strcmp(leaderboardExpert[i].name,game5x5->playerBlue.name)==0){
            found=1;
            if(leaderboardExpert[i].score<game5x5->playerBlue.score){
                leaderboardExpert[i].score=game5x5->playerBlue.score;
            }
        }
    }
    if(found==0){
        sprintf(leaderboardExpert[255].name,"%s",game5x5->playerBlue.name);
        leaderboardExpert[255].score=game5x5->playerBlue.score;
    }
    sortListExpert();
    for(int i=0;i<256;i++){
        fprintf(mainFile,"ExpertMode - %s with score: %d\n",leaderboardExpert[i].name,leaderboardExpert[i].score);
    }
    fclose(mainFile);
}

//show ExpertMode leaderboard
void showLeaderboardExpert(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    for(int i=0;i<10;i++){
        menuNums1(renderer,i+1,WINDOW_WIDTH/4,WINDOW_HEIGHT*(2*i+1)/20,0,255);
        menuText(renderer,leaderboardExpert[i].name,WINDOW_WIDTH/2,WINDOW_HEIGHT*(2*i+1)/20,255,0);
        menuNums2(renderer,leaderboardExpert[i].score,WINDOW_WIDTH*3/4,WINDOW_HEIGHT*(2*i+1)/20,0,255);
    }
    SDL_RenderPresent(renderer);
}

//show EasyMode leaderboard
void showLeaderboardEasy(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    for(int i=0;i<10;i++){
        menuNums1(renderer,i+1,WINDOW_WIDTH/4,WINDOW_HEIGHT*(2*i+1)/20,0,255);
        menuText(renderer,leaderboardEasy[i].name,WINDOW_WIDTH/2,WINDOW_HEIGHT*(2*i+1)/20,255,0);
        menuNums2(renderer,leaderboardEasy[i].score,WINDOW_WIDTH*3/4,WINDOW_HEIGHT*(2*i+1)/20,0,255);
    }
    SDL_RenderPresent(renderer);
}

//Render leaderboard menu
void doRenderLeaderboard(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rect={0,WINDOW_HEIGHT/2-5,WINDOW_WIDTH,10};
    SDL_RenderFillRect(renderer,&rect);
    menuText(renderer,"EasyMode Leaderboard",WINDOW_WIDTH/2,WINDOW_HEIGHT/4,255,0);
    menuText(renderer,"ExpertMode Leaderboard",WINDOW_WIDTH/2,WINDOW_HEIGHT*3/4,0,255);
    SDL_RenderPresent(renderer);
}

//Loop of leaderboard menu
int doLoopLeaderboard(SDL_Window *window){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.y>0 && event.button.y<WINDOW_HEIGHT/2-5){ //upper half
                    state=EASYLEADERBOARD;
                }
                else if(event.button.y>WINDOW_HEIGHT/2+5 && event.button.y<WINDOW_HEIGHT){ //lower half
                    state=EXPERTLEADERBOARD;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
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
        }
    }

    return done;
}

//inner leaderboards loop
int doLoopLeaderboardE(SDL_Window *window){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        state=LEADERBOARD;
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
        }
    }

    return done;
}


#endif