#ifndef NAMEGET_H
#define NAMEGET_H
#include "includes.h"
#include "defines.h"
#include "structs.h"
#include "showMainMenu.h"
#include <ctype.h>

//show getName screen for EasyMode vs player
void doRendergetName2x2(SDL_Renderer *renderer,gameState2x2 *game2x2,int player){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    if(player==0){ //if red player chosen
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_Rect rect={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT/4+50,500,10};
        SDL_RenderFillRect(renderer,&rect);
    }
    else{ //if blue player chosen
        SDL_SetRenderDrawColor(renderer,0,0,255,255);
        SDL_Rect rect={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT*3/4+50,500,10};
        SDL_RenderFillRect(renderer,&rect);
    }
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rect1={0,WINDOW_HEIGHT/2-5,WINDOW_WIDTH,10};
    SDL_Rect rect2={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT/4-60,500,120}; //show text outline box
    SDL_Rect rect3={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT*3/4-60,500,120}; //show text outline box
    SDL_RenderFillRect(renderer,&rect1);
    SDL_RenderDrawRect(renderer,&rect2);
    SDL_RenderDrawRect(renderer,&rect3);
    menuBottomText(renderer,"*don't use spaces and only use lowercase",5,WINDOW_HEIGHT,20);
    menuTopText(renderer,"Press Enter to start game",WINDOW_WIDTH/2,0,32);
    menuText(renderer,"Red Player's name",WINDOW_WIDTH/4,WINDOW_HEIGHT/4,255,0);
    menuText(renderer,"Blue Player's name",WINDOW_WIDTH/4,WINDOW_HEIGHT*3/4,0,255);
    menuText(renderer,game2x2->playerRed.name,WINDOW_WIDTH*3/4,WINDOW_HEIGHT/4,255,0); //show red player's name
    menuText(renderer,game2x2->playerBlue.name,WINDOW_WIDTH*3/4,WINDOW_HEIGHT*3/4,0,255); //show blue player's name
    SDL_RenderPresent(renderer);
}

//main loop for getName EasyMode vs player screen
int doLoopgetName2x2(SDL_Window *window,gameState2x2 *game2x2,int *player){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.y>0 && event.button.y<WINDOW_HEIGHT/2-5){ //click on top half to change red player's name
                    *player=0;
                }
                else if(event.button.y>WINDOW_HEIGHT/2+5 && event.button.y<WINDOW_HEIGHT){ //click on top half to change blue player's name
                    *player=1;
                }
            case SDL_TEXTINPUT: //enter names
                if(*player==0){
                    strcat(game2x2->playerRed.name,event.text.text);
                }
                else if(*player==1){
                    strcat(game2x2->playerBlue.name,event.text.text);
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_BACKSPACE: //deleting name
                        if(*player==0){
                            for(int i=0;i<128;i++){
                                if(game2x2->playerRed.name[i]=='\0'){
                                    game2x2->playerRed.name[i-1]='\0';
                                    break;
                                }
                            }
                        }
                        else if(*player==1){
                            for(int i=0;i<128;i++){
                                if(game2x2->playerBlue.name[i]=='\0'){
                                    game2x2->playerBlue.name[i-1]='\0';
                                    break;
                                }
                            }
                        }
                        break;
                    case SDLK_RETURN: //go to game
                        oldTime=clock();
                        state=EASY;
                        break;
                    case SDLK_ESCAPE: //exit game
                        state=MAINMENU;
                        break;
                }
                break;
            case SDL_QUIT: //exit game using X
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

//show getName screen for ExpertMode vs player
void doRendergetName5x5(SDL_Renderer *renderer,gameState5x5 *game5x5,int player){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    if(player==0){ //if red player chosen
        SDL_SetRenderDrawColor(renderer,255,0,0,255);
        SDL_Rect rect={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT/4+50,500,10};
        SDL_RenderFillRect(renderer,&rect);
    }
    else{ //if blue player chosen
        SDL_SetRenderDrawColor(renderer,0,0,255,255);
        SDL_Rect rect={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT*3/4+50,500,10};
        SDL_RenderFillRect(renderer,&rect);
    }
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rect1={0,WINDOW_HEIGHT/2-5,WINDOW_WIDTH,10};
    SDL_Rect rect2={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT/4-60,500,120}; //show text outline box
    SDL_Rect rect3={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT*3/4-60,500,120}; //show text outline box
    SDL_RenderFillRect(renderer,&rect1);
    SDL_RenderDrawRect(renderer,&rect2);
    SDL_RenderDrawRect(renderer,&rect3);
    menuBottomText(renderer,"*don't use spaces and only use lowercase",5,WINDOW_HEIGHT,20);
    menuTopText(renderer,"Press Enter to start game",WINDOW_WIDTH/2,0,32);
    menuText(renderer,"Red Player's name",WINDOW_WIDTH/4,WINDOW_HEIGHT/4,255,0);
    menuText(renderer,"Blue Player's name",WINDOW_WIDTH/4,WINDOW_HEIGHT*3/4,0,255);
    menuText(renderer,game5x5->playerRed.name,WINDOW_WIDTH*3/4,WINDOW_HEIGHT/4,255,0); //show red player's name
    menuText(renderer,game5x5->playerBlue.name,WINDOW_WIDTH*3/4,WINDOW_HEIGHT*3/4,0,255); //show blue player's name
    SDL_RenderPresent(renderer);
}

//main loop for getName ExpertMode vs player screen
int doLoopgetName5x5(SDL_Window *window,gameState5x5 *game5x5,int *player){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.y>0 && event.button.y<WINDOW_HEIGHT/2-5){ //click on top half to change red player's name
                    *player=0;
                }
                else if(event.button.y>WINDOW_HEIGHT/2+5 && event.button.y<WINDOW_HEIGHT){ //click on top half to change blue player's name
                    *player=1;
                }
            case SDL_TEXTINPUT: //enter names
                if(*player==0){
                    strcat(game5x5->playerRed.name,event.text.text);
                }
                else if(*player==1){
                    strcat(game5x5->playerBlue.name,event.text.text);
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_BACKSPACE: //deleting name
                        if(*player==0){
                            for(int i=0;i<128;i++){
                                if(game5x5->playerRed.name[i]=='\0'){
                                    game5x5->playerRed.name[i-1]='\0';
                                    break;
                                }
                            }
                        }
                        else if(*player==1){
                            for(int i=0;i<128;i++){
                                if(game5x5->playerBlue.name[i]=='\0'){
                                    game5x5->playerBlue.name[i-1]='\0';
                                    break;
                                }
                            }
                        }
                        break;
                    case SDLK_RETURN: //go to game
                        oldTime=clock();
                        state=EXPERT;
                        break;
                    case SDLK_ESCAPE: //exit game
                        state=MAINMENU;
                        break;
                }
                break;
            case SDL_QUIT: //exit game using X
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

//show getName screen for EasyMode vs AI
void doRendergetName2x2_2(SDL_Renderer *renderer,gameState2x2 *game2x2){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_Rect rect1={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT/2+50,500,10};
    SDL_RenderFillRect(renderer,&rect1);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rect2={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT/2-60,500,120}; //show text outline box
    SDL_RenderDrawRect(renderer,&rect2);
    menuBottomText(renderer,"*don't use spaces and only use lowercase",5,WINDOW_HEIGHT,20);
    menuTopText(renderer,"Press Enter to start game",WINDOW_WIDTH/2,0,32);
    menuText(renderer,"Red Player's name",WINDOW_WIDTH/4,WINDOW_HEIGHT/2,255,0);
    menuText(renderer,game2x2->playerRed.name,WINDOW_WIDTH*3/4,WINDOW_HEIGHT/2,255,0); //show red player's name
    SDL_RenderPresent(renderer);
}

//main loop for getName EasyMode vs AI screen
int doLoopgetName2x2_2(SDL_Window *window,gameState2x2 *game2x2){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_TEXTINPUT: //enter name
                strcat(game2x2->playerRed.name,event.text.text);
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_BACKSPACE: //deleting name
                        for(int i=0;i<128;i++){
                            if(game2x2->playerRed.name[i]=='\0'){
                                game2x2->playerRed.name[i-1]='\0';
                                break;
                            }
                        }
                        break;
                    case SDLK_RETURN: //go to game
                        oldTime=clock();
                        state=EASY;
                        break;
                    case SDLK_ESCAPE: //exit game
                        state=MAINMENU;
                        break;
                }
                break;
            case SDL_QUIT: //exit game using X
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

//show getName screen for ExpertMode vs AI
void doRendergetName5x5_2(SDL_Renderer *renderer,gameState5x5 *game5x5){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    SDL_Rect rect1={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT/2+50,500,10};
    SDL_RenderFillRect(renderer,&rect1);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_Rect rect2={WINDOW_WIDTH*3/4-250,WINDOW_HEIGHT/2-60,500,120}; //show text outline box
    SDL_RenderDrawRect(renderer,&rect2);
    menuBottomText(renderer,"*don't use spaces and only use lowercase",5,WINDOW_HEIGHT,20);
    menuTopText(renderer,"Press Enter to start game",WINDOW_WIDTH/2,0,32);
    menuText(renderer,"Red Player's name",WINDOW_WIDTH/4,WINDOW_HEIGHT/2,255,0);
    menuText(renderer,game5x5->playerRed.name,WINDOW_WIDTH*3/4,WINDOW_HEIGHT/2,255,0); //show red player's name
    SDL_RenderPresent(renderer);
}

//main loop for getName ExpertMode vs AI screen
int doLoopgetName5x5_2(SDL_Window *window,gameState5x5 *game5x5){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_TEXTINPUT: //enter name
                strcat(game5x5->playerRed.name,event.text.text);
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_BACKSPACE: //deleting name
                        for(int i=0;i<128;i++){
                            if(game5x5->playerRed.name[i]=='\0'){
                                game5x5->playerRed.name[i-1]='\0';
                                break;
                            }
                        }
                        break;
                    case SDLK_RETURN: //go to game
                        oldTime=clock();
                        state=EXPERT;
                        break;
                    case SDLK_ESCAPE: //exit game
                        state=MAINMENU;
                        break;
                }
                break;
            case SDL_QUIT: //exit game using X
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