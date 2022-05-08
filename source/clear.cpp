/***************************
** author: lyl
** time: 5/20/2021
** version: v1
** function: clear命令
**************************/

#include "clear.h"

int main(){
    fflush(stdout);
    printf("\033[H\033[2J");
    return 0;
}