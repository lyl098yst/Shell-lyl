/***************************
** author: lyl
** time: 5/9/2021
** version: v1
** function: wc命令 + 管道
**************************/
#include "wc.h"

using namespace std;
int main(int argc, char* argv[]){
    //行数 字数 字节数 和 名称
    if(argc <= 2){
        cout << "Too few arguments" <<endl;
    }

    if(strcmp(argv[argc-2], "pipe") == 0){
        //cout << "pipe cmd" <<endl;
        //从管道读取数据
        //第一个参数是cat, 第二个参数是匹配的字符， 第三个参数是文件
        int k = argv[argc-1][0] + '0';//获取管道读端
        //用于存放管道读取出来的数据
        char buff[1024*1024];   
        int buffLength;
        read(k,buff,1024*1024);
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
        // for(int i=0;i<lineN;i++){
        //     cout<<lines[i]<<endl;
        // }
        cout << "行数为：" << lineN << endl;
        return 0;
    }

    if(argc >= 4){
        cout << "Too many arguments" <<endl;
    }
    string filename = argv[1];
    filename = MAIN_PATH + filename;
    ifstream in(filename.c_str()); 
    string line;
    int lineCount = 0;
    int wordCount = 0;
    string buffer = "";
    if(in){//有该文件 
        while(getline(in, line)){
            buffer+=line;
            //line中不包括每行的换行符
            lineCount++;
            if(line.length() == 0){
                continue;
            }
            //cout<<line<<endl;
            for(int i = 0; i < line.length(); i++){
                if(line[i] == ' '){
                    wordCount++;
                    //cout<<lineCount<<" : "<<i<<endl;
                }
            }
            wordCount++;
        }  
        
        printf("File: %s: Word Count:%d Line Count:%d\n",argv[1], wordCount, lineCount);
    }else{
        //没有该文件或者打开出错
        cout <<"Open file fail." << endl;  
    }    
    return 0;
}


