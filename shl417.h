#include "color.cpp"
#include <iostream>
#include <unistd.h>
#include <pwd.h> 
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <exception>
#include <vector>
#include <fstream> 
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <string.h>
#include <cstring>
#include "source/cd.cpp"
#include "config.h"
using namespace std;

//command存放输入的字符串：命令+参数
char* cmdString;
//解析command，将命令、参数、类型存放到结构体中
struct cmdRes{
    int type;
    /*type
    * -1: error cmd
    * 0: ordinary
    * 1: pipe
    * 2: redirect
    */
    char * redirectPath;//重定向的目录

    int cmdcount;//有多少pipe命令
    struct cmdRes* pipeCmds[MAX_PIPE_CMD];//管道命令
    
    int paracount;//有多少参数
    //第一个参数是命令，最后一个参数是输入的字符串，中间是解析的参数
    char *parameters[MAX_ARG];//存放解析出来的参数

    cmdRes() : paracount(0){}
}analyze_res;

//获取标识符
void get_Identify();

//获取用户输入的命令字符串
int get_CmdString();

//对用户输入的命令字符串进行解析
void get_CmdRes();

//对管道命令字符串进行解析
void analyze_PipeCmd();

//对重定向命令字符串进行解析
void analyze_RedirectCmd();

//执行普通命令
void excute_OrdinaryCmd();

//执行管道命令
void excute_PipeCmd();

//执行重定向命令
void excute_RedirectCmd();

//检查命令是否存在
int checkCmd(char * cmd);

//获取历史命令列表
vector<string> get_History();

struct cmdRes* analyze_OrdinaryCmd(char * cmd);
void help();