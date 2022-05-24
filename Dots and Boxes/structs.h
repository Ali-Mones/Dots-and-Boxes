#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct{
    int type,x,y;
}gameArray; //turns struct

typedef struct{
    int x,y;
} Dots; //dot struct

typedef struct{
    int val;
    int red;
    int blue;
} horLine; //horizontal line struct

typedef struct{
    int x,y;
    int val;
    int red,blue;
} Box; //box struct

typedef struct{
    int val;
    int red;
    int blue;
} verLine; //vertical line struct

typedef struct{
    char name[128];
    int score;
    char colour;
}players; //player struct

typedef struct{
    char name[128];
    int score;
} winners; //leaderboard struct

typedef struct{
    horLine hLine[3][2];
    verLine vLine[2][3];
    int player;
    Box box[2][2];
    gameArray A[12];
    players playerRed;
    players playerBlue;
    int turn;
} gameState2x2; //2x2 game struct

typedef struct{
    horLine hLine[6][5];
    verLine vLine[5][6];
    int player;
    Box box[5][5];
    gameArray A[60];
    players playerRed;
    players playerBlue;
    int turn;
} gameState5x5; //5x5 game struct

typedef struct{
    int x,y;
}validVertical; //valid vertical lines struct used by ai

typedef struct{
    int x,y;
}validHorizontal; //valid horizontal lines struct used by ai

#endif