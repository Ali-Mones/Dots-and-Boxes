#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    int sec=0;
    if(clock()%CLOCKS_PER_SEC==0){
        sec++;
        printf("%d",sec);
    }
    if(clock()%CLOCKS_PER_SEC==0){
        sec++;
        printf("%d",sec);
    }
    return 0;
}