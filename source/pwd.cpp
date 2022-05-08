/***************************
** author: lyl
** time: 5/7/2021
** version: v1
** function: pwd命令
**************************/
#include "pwd.h"

using namespace std;

int main(int argc, char *argv[]){
    getcwd(dir, MAX_PWD_LENGTH);
    cout << dir << endl;
    return 0;
}