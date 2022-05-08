/***************************
** author: lyl
** time: 5/9/2021
** version: v1
** function: mkdir命令
**************************/
#include "mkdir.h"

using namespace std;
//mkdir dir mkdi-
int main(int argc, char* argv[]){
    if(argc <= 2){
        cout << "Too few arguments" <<endl;
        return 0;
    }
    if(argc >= 10){
        cout << "Too many arguments" <<endl;
        return 0;
    }
    for(int i = 1; i < argc - 1; i++){
        if(mkdir(argv[i], 0755) != 0){
            printf("Make director failed:%s\n", argv[i]);
        }
    }
}