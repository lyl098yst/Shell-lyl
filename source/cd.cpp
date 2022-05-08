/***************************
** author: lyl
** time: 5/16/2021
** version: v1
** function: cd命令
**************************/
#include "cd.h"
using namespace std;
int change_dir(char* newPath){
    return chdir(newPath);
}