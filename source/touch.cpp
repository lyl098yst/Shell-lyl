/***************************
** author: lyl
** time: 5/9/2021
** version: v1
** function: touch命令
**************************/
#include "mkdir.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc <= 2){
        cout << "Too few arguments" <<endl;
        return 0;
    }
    if(argc >= 10){
        cout << "Too many arguments" <<endl;
        return 0;
    }
    FILE *file;
    try{
        for(int i = 1; i < argc - 1; i++){
            if((file = fopen(argv[i], "w"))){
                cout << "Touch file success:" << argv[i] <<endl;
            }else{
                cout << "Touch file fail:" << argv[i] <<endl;
            }
        }
    }catch(exception e){
        fclose(file);
        //需要指向空，否则会指向原打开文件地址
        file = NULL;
    }
}