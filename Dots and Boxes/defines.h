#ifndef DEFINES_H
#define DEFINES_H

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define horizontal -1
#define vertical 2
#define MAINMENU 0
#define NEWGAME 1
#define LOADGAME 2
#define LEADERBOARD 3
#define EASY 4
#define EXPERT 5
#define VS 6
#define EASYLEADERBOARD 7
#define EXPERTLEADERBOARD 8
#define SAVES2X2 9
#define SAVES5X5 10
#define CHOOSEVS 11
#define GETNAME2x2 12
#define GETNAME5X5 13
#define GETNAME2X2VSAI 14
#define GETNAME5X5VSAI 15

int state=MAINMENU;
FILE *mainFile;
winners leaderboardEasy[256];
winners leaderboardExpert[256];
int ai=0;
clock_t oldTime=0;
#endif