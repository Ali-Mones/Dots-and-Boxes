#ifndef SHOWMENU_H
#define SHOWMENU_H
#include "defines.h"
#include "includes.h"

//show numbers for leaderboard rankings
void menuNums1(SDL_Renderer *renderer,int val,int x,int y,int red,int blue){
    int txtW,txtH;
    char text[3];
    sprintf(text,"%d)",val);
    TTF_Font *font=TTF_OpenFont("comicsans.ttf",48);
    SDL_Colour white={255,255,255,255};
    SDL_Colour colour={red,0,blue,255};
    SDL_Surface *msg= TTF_RenderText_Shaded(font,text,colour,white);
    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(texture,0,0,&txtW,&txtH);
    SDL_Rect txtrect={x-txtW/2,y-txtH/2,txtW,txtH};
    SDL_RenderCopy(renderer,texture,0,&txtrect);
    SDL_DestroyTexture(texture);
}

//show leaderboard scores
void menuNums2(SDL_Renderer *renderer,int val,int x,int y,int red,int blue){
    int txtW,txtH;
    char text[16];
    sprintf(text,"Score: %d",val);
    TTF_Font *font=TTF_OpenFont("comicsans.ttf",48);
    SDL_Colour white={255,255,255,255};
    SDL_Colour colour={red,0,blue,255};
    SDL_Surface *msg= TTF_RenderText_Shaded(font,text,colour,white);
    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(texture,0,0,&txtW,&txtH);
    SDL_Rect txtrect={x-txtW/2,y-txtH/2,txtW,txtH};
    SDL_RenderCopy(renderer,texture,0,&txtrect);
    SDL_DestroyTexture(texture);
}

//show text in menus
void menuText(SDL_Renderer *renderer,char text[128],int x,int y,int red,int blue){
    int txtW,txtH;
    TTF_Font *font=TTF_OpenFont("comicsans.ttf",48);
    SDL_Colour white={255,255,255,255};
    SDL_Colour colour={red,0,blue,255};
    SDL_Surface *msg= TTF_RenderText_Shaded(font,text,colour,white);
    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(texture,0,0,&txtW,&txtH);
    SDL_Rect txtrect={x-txtW/2,y-txtH/2,txtW,txtH};
    SDL_RenderCopy(renderer,texture,0,&txtrect);
    SDL_DestroyTexture(texture);
}

//show text at bottom of menus
void menuBottomText(SDL_Renderer *renderer,char text[128],int x,int y,int size){
    int txtW,txtH;
    TTF_Font *font=TTF_OpenFont("comicsans.ttf",size);
    SDL_Colour black={0,0,0,255};
    SDL_Surface *msg= TTF_RenderText_Blended(font,text,black);
    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(texture,0,0,&txtW,&txtH);
    SDL_Rect txtrect={x,y-txtH,txtW,txtH};
    SDL_RenderCopy(renderer,texture,0,&txtrect);
    SDL_DestroyTexture(texture);
}

//show text at top of menus
void menuTopText(SDL_Renderer *renderer,char text[128],int x,int y,int size){
    int txtW,txtH;
    TTF_Font *font=TTF_OpenFont("comicsans.ttf",size);
    SDL_Colour black={0,0,0,255};
    SDL_Surface *msg= TTF_RenderText_Blended(font,text,black);
    SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer,msg);
    SDL_FreeSurface(msg);
    SDL_QueryTexture(texture,0,0,&txtW,&txtH);
    SDL_Rect txtRect={x-txtW/2,0,txtW,txtH};
    SDL_RenderCopy(renderer,texture,0,&txtRect);
    SDL_DestroyTexture(texture);
}

//show mainmenu
void doRenderMainMenu(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    //general shape
    SDL_Rect rect1={0,WINDOW_HEIGHT/4-5,WINDOW_WIDTH,10};
    SDL_Rect rect2={0,WINDOW_HEIGHT*2/4-5,WINDOW_WIDTH,10};
    SDL_Rect rect3={0,WINDOW_HEIGHT*3/4-5,WINDOW_WIDTH,10};
    SDL_RenderFillRect(renderer,&rect1);
    SDL_RenderFillRect(renderer,&rect2);
    SDL_RenderFillRect(renderer,&rect3);
    //show text
    menuText(renderer,"New Game",WINDOW_WIDTH/2,WINDOW_HEIGHT/8,255,0);
    menuText(renderer,"Load Game",WINDOW_WIDTH/2,WINDOW_HEIGHT*3/8,0,255);
    menuText(renderer,"Leaderboard",WINDOW_WIDTH/2,WINDOW_HEIGHT*5/8,255,0);
    menuText(renderer,"Exit",WINDOW_WIDTH/2,WINDOW_HEIGHT*7/8,0,255);
    SDL_RenderPresent(renderer);
}

//mainmenu loop
int doLoopMainMenu(SDL_Window *window){
    SDL_Event event;
    int done=0;
    while (SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.y>0 && event.button.y<WINDOW_HEIGHT/4-5){
                    state=CHOOSEVS;
                }
                else if(event.button.y>WINDOW_HEIGHT/4+5 && event.button.y<WINDOW_HEIGHT*2/4-5){
                    state=LOADGAME;
                }
                else if(event.button.y>WINDOW_HEIGHT*2/4+5 && event.button.y<WINDOW_HEIGHT*3/4-5){
                    state=LEADERBOARD;
                }
                else if(event.button.y>WINDOW_HEIGHT*3/4+5 && event.button.y<WINDOW_HEIGHT){ //exit game
                    done=1;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE: //exit game
                        done=1;
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