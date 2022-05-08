/***************************
** author: lyl
** time: 5/20/2021
** version: v1
** function: cat命令 + 管道
**************************/
#include "cat.h"
using namespace std;

int main(int argc, char* argv[]){
    if(argc <= 2){
        //cout << "Too few arguments" <<endl;
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

    if(strcmp(argv[argc-2], "pipe") == 0){
        //cout << "pipe cmd" <<endl;
        //从管道读取数据
        //第一个参数是cat, 第二个参数是匹配的字符， 第三个参数是文件
        int k = argv[argc-1][0] + '0';//获取管道读端
        //用于存放管道读取出来的数据
        char buff[1024*1024];   
        int buffLength;
        read(k, buff, 1024*1024);
        buffLength = strlen(buff);
        //用于存放处理之后的管道数据
        char lines[1024][1024];
        int lineN = 0;//有多少行
        int lineC = 0;//一行有多少字符
        for(int i = 0;i < buffLength;i++){
            if(buff[i] == '\n'){
                lines[lineN][lineC++] = '\0';
                lineN++;
                lineC = 0;
            }else{
                lines[lineN][lineC++] = buff[i];
            }
        }
        for(int i = 0; i < lineN; i++){
                cout << lines[i] << endl;
        }
        return 0;
    }

    if(argc >= 4){
        cout << "Too many arguments" <<endl;
        return 0;
    }
    string filename = argv[1]; 
    filename = MAIN_PATH + filename;
    ifstream in(filename.c_str());
    string line;
    if(in){//有该文件 
        while(getline(in,line)){// line中不包括每行的换行符     
            cout << line << endl;
        }
        in.close();
    }else{
        //没有该文件或者打开出错
        cout <<"Open file fail." << endl;  
    } 
}