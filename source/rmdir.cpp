/***************************
** author: lyl
** time: 5/10/2021
** version: v1
** function: rm命令
**************************/
#include "rm.h"

using namespace std;
int main(int argc, char* argv[]){
    if(argc <= 2){
        cout << "Too few arguments" << endl;
        return 0;
    }
    if(argc >= 10){
        cout << "Too few arguments" << endl;
        return 0;
    }
    //判断是否是文件，如果是目录必须适用rmdir
    for(int i = 1; i < argc - 1; i++){        
        struct stat buf;
        stat(argv[i], &buf);
        if(!S_ISDIR(buf.st_mode)){
            cout << "The file must be a directory" <<endl;
            return 0;
        }else{
            ///remove()函数返回值为0或EPF(-1)
            int flag = remove(argv[i]);  
            if(flag == 0){
                cout << "Delete success！" << endl;
            }else{
                cout << "Delete error：" << endl;
                //perror("remove");
            }
        }
    }
    return 0;
}