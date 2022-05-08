/***************************
** author: lyl
** time: 5/7/2021
** version: v1
** function: echo命令
**************************/
#include "echo.h"

using namespace std;

int main(int argc,char *argv[]){
    //首先判断参数里面是否有'或者"
    if(argc <= 2){
        //cout << "Input None" << endl;
        char catNoPara [100] = "\0";
        while(true){
            cin.getline(catNoPara,100);
            if(strcmp(catNoPara, "exit") == 0){
                return 0;
            }
            cout << catNoPara << endl;

        }
        return 0;
    }
    int countn = 0;
    int countm = 0;
    string para = argv[argc - 1];
    for(int i = 0; i < para.length(); i++){
        if(para[i] == '\''){
            countn++;
        }
        if(para[i] == '\"'){
            countm++;
        }
    }
    if((countm + countn) % 2 ==1 || countm%2==1){
        //count必须为偶数
        cout << "Parameters error!" << endl;
    }else{
        int beg = 5;
        int end = para.length()-1;
        while(beg <= end){
            if((para[beg] == '\"' && para[end] == '\"') || (para[beg] == '\'' && para[end] == '\'')){
                beg++; 
                end--;
            }else{
                if(para[beg] == '\"' || para[beg] == '\''){
                    beg++;
                    continue;
                }else{
                    cout << para[beg++];
                }
            }
        }
        cout << endl;
    }
    return 0;
}
