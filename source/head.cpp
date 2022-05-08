/***************************
** author: lyl
** time: 5/20/2021
** version: v1
** function: head命令 + 管道
**************************/
#include "head.h"
using namespace std;

int main(int argc, char* argv[]){
    if(argc <= 2){
        cout << "Too few arguments" <<endl;
        return 0;
    }

    if(strcmp(argv[argc-2], "pipe") == 0){
        //cout << "pipe cmd" <<endl;
        //从管道读取数据
        //第一个参数是cat, 第二个参数是匹配的字符， 第三个参数是文件
        int k = argv[argc - 1][0] + '0';//获取管道读端
        //用于存放管道读取出来的数据
        char buff[1024 * 1024];   
        int buffLength;
        read(k, buff, 1024 * 1024);
        //cout<<buff<<endl;
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
        string line = argv[1];
        int num = 0;
        bool flag = false;//是输入的0还是默认的0，默认的0要改成10
        for(int j = 0; j < line.length(); j++){
            if(line[j] >= '0' && line[j] <= '9'){
                num = num * 10 + (line[j] - '0');
                flag = true;
            }
        }
        if(num == 0){
            //cout<<"num=0"<<endl;
            if(!flag){
                num=10;
                //cout<<"num=10"<<endl;
            }
        }
        //cout << num << endl;
        if(num > lineN){
            num = lineN;
        }
        for(int i = 0; i < num; i++){
            cout << lines[i] << endl;
        }
        return 0;
    }else if(argc == 3){
        //假设是只输入文件名，此时默认输出前10行
        int num = 10;
        string line;
        string filename = argv[1];
        ifstream in(MAIN_PATH + filename);
        if(in){//有该文件 
            while(getline(in,line) && num){
                // line中不包括每行的换行符
                cout << line << endl;
                num--;
            }
            in.close();
        }else{
            //没有该文件或者打开出错
            cout <<"Open file fail." << endl;  
        } 
        return 0;
    }

    if(argc > 4){
        cout << "Too many arguments" <<endl;
        return 0;
    }
    //head -行数 文件名 head+文件名/（pipe 管道号）
    //获取行数
    string line = argv[1];
    int num = 0;
    for(int j = 0; j < line.length(); j++){
        if(line[j] >= '0' && line[j] <= '9'){
            num = num * 10 + (line[j] - '0');
        }
    }
    //cout << num << endl;
    //打开文件
    string filename = argv[2];
    filename = MAIN_PATH + filename;
    ifstream in(filename.c_str()); 
    if(in){//有该文件 
        while(getline(in,line) && num){
            // line中不包括每行的换行符
            cout << line << endl;
            num--;
        }
        in.close();
    }else{
        //没有该文件或者打开出错
        cout <<"Open file fail." << endl;  
    } 
}