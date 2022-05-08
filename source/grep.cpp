/***************************
** author: lyl
** time: 5/20/2021
** version: v1
** function: grep命令 + 管道
**************************/

#include "grep.h"

using namespace std;
int main(int argc, char* argv[]){
    if(argc <= 2){
        cout << "Too few arguments" << endl;
        return 0;
    }
    //判断是否是管道
    if(strcmp(argv[argc-2], "pipe") == 0){
        //grep cpp pipe des
        if(argc == 3){
            cout << "Too few arguments" << endl;
            return 0;
        }
        //cout << "pipe cmd" <<endl;
        //从管道读取数据
        //第一个参数是grep, 第二个参数是匹配的字符， 第三个参数是文件
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
            if(strstr(lines[i], argv[argc - 3]) != NULL){
                cout << lines[i] << endl;
            }
        }
        return 0;
    }else if(argc == 3){
        //grep a.cpp cpp grp--
        //判断是否是命令出错
        cout << "Error command!" << endl;
        return 0;
    }
    if(argc >= 5){
        cout << "Too much arguments" << endl;
        return 0;
    }
    //否则就是打开文件然后判断输出
    //grep 文件 匹配 全部
    //文件参数是 argc - 3 , 匹配符号是 argc - 2
    string filename = argv[argc - 3];
    filename = MAIN_PATH + filename;
    ifstream in(filename.c_str()); 
    string line;
    int lineNum = 1;
    if(in){//有该文件 
        while(getline(in, line)){// line中不包括每行的换行符     
            if(strstr(line.c_str(), argv[argc - 2]) != NULL){
                cout << line << endl;
            }
        }
        in.close();
    }else{
        //没有该文件或者打开出错
        cout <<"Open file fail." << endl;  
    } 
    return 0;
}