/***************************
** author: lyl
** time: 5/6/2021
** version: v1
** function: shell主界面
**************************/

#include "shl417.h"
using namespace std;
//运行主函数
int main(){
    fflush(stdout);
    printf("\033[H\033[2J");
    cout << "若第一次使用，请输入 help，回车来查看帮助" << endl;
    //使用一个死循环不断显示标识符并获取用户输入命令
    while(true){
        //首先获取标识符,根据颜色输出
        get_Identify();
        //获取输入的字符串
        int get_cmdString_res = get_CmdString();
        //如果什么都没输入直接continue;
        if(get_cmdString_res == 0) continue;
        //exit指令就退出;
        if(get_cmdString_res == -1) return 0;
        //否则就，初步解析字符串，获取命令和参数
        get_CmdRes();
        //解析完之后执行命令
        switch(analyze_res.type){
            case 0: excute_OrdinaryCmd(); break;
            case 1: excute_PipeCmd(); break;
            case 2: excute_RedirectCmd(); break;            
            case -1: cout << "Error Command !" << endl; break;
        }
    }
    return 0;
}
//获取标识符
void get_Identify(){
    /**
    * input: 使用全局变量identify，将标识符信息存放到这里
    * output: identify
    */    
    struct passwd *pwd = getpwuid(getuid());//pwd存放用户信息

    char hostName[MAX_NAME_LEN]; //hostName主机名
    //获取主机名，返回0为成功,存放用户名，主机名
    if(gethostname(hostName,MAX_NAME_LEN) == 0){
        cout << GREEN << pwd->pw_name << "@" << hostName << RESET << ":";
    }else{
        cout << "Fail to get hostname." << endl;
    }

    char pathName[MAX_NAME_LEN]; //pathName路径名
    //getcwd()会将当前工作目录的绝对路径复制到参数buffer所指的内存空间中
    getcwd(pathName,MAX_NAME_LEN); //获取当前工作路径存放到pathName中
    
    if(strlen(pathName) < strlen(pwd->pw_dir) || strncmp(pathName, pwd->pw_dir, strlen(pwd->pw_dir)) != 0){
        cout << BLUE << pathName << RESET;
    }else{
        cout << BLUE << "~" << pathName << RESET;
    }

    if(geteuid() == 0){ 
        //root用户
        cout << "#";
    }else{
        //普通用户
        cout << "$";
    }
}
//获取用户输入的命令字符串
int get_CmdString(){
    /**
    * input: cmdString，将读取得命令存放到这里
    * output: int: 1:success -1:exit 0:NULL
    */  
    if(cmdString){
        free(cmdString);
        cmdString = NULL;
    }
    //使用了readline.h 实现Tab键自动补全以及删除键删除功能
    cmdString = readline(" ");
    //退出指令
    if(strcmp(cmdString, "exit") == 0){
        //退出命令exit
        free(cmdString);
        cmdString = NULL;
        return -1;
    }
    //空指令
    if(strcmp(cmdString, "\0") == 0){
        //空指令
        free(cmdString);
        cmdString = NULL;
        return 0;
    }
    //这是一个!命令
    if(cmdString[0] == '!'){
        //首先获取历史记录
        vector<string> history = get_History();
        if(strcmp(cmdString,"!!")==0){
            if(history.size()==0){
                cout <<"no commands in history" << endl;  
                return 0;
            }
            strcpy(cmdString, history[history.size() - 1].c_str());
            cout << "!!：" << cmdString << endl;
        }else if(cmdString[0] == '!' && (cmdString[1] < '0' || cmdString[1] > '9')){
            cout << "! + 命令字母" << endl;
            int b_i=1;
            //每一条指令开始比较，从后往前比较
            for(int i = history.size()-1; i >= 0; --i){
                while(cmdString[b_i] != '\0' && history[i][b_i-1] != '\0'){
                    if(history[i][b_i-1] != cmdString[b_i]){
                        break;
                    }else{
                        b_i++;
                    }
                }
                if(cmdString[b_i]=='\0'){
                    strcpy(cmdString, history[i].c_str());
                    break;
                }
            }
        }else if(cmdString[0] == '!' && (cmdString[1] >= '0' && cmdString[1] <= '9')){
            cout << "! + 命令编号" << endl;
            int number = 0;//命令编号
            int i = 1;
            while(cmdString[i] != '\0'){
                number = number * 10 + int(cmdString[i++] - '0');
            }
            if(number < history.size()){
                strcpy(cmdString, history[number].c_str());
            }else{
                cout <<"No such commands in history" << endl; 
                return -1;
            }
        }
    }
    return 1;
}
//对用户输入的命令字符串进行解析
void get_CmdRes(){
    /**
    * input: cmdString，解析该命令将命令和参数存放到结构体中
    * output: cmdRes: analyze_res
    */    
    char *temp_cmdString = strdup(cmdString);
    //这里需要复制而不是直接复制，因为是指针，cmdString在后面被修改了
    //如果不是!命令则将命令添加到历史
    if(cmdString[0] != '!'){
        add_history(cmdString);
        write_history(HISTORY_PATH);
    }
    //思路，先遍历一次这个字符串，判断是管道还是重定向
    int ispipe = 0;
    int isredirect = 0;
    //解析命令，构建一个结构体analyze_res并初始化
    analyze_res.paracount = 0;
    analyze_res.cmdcount = 0;
    analyze_res.type = 0;
    //解析命令思路：首先将所有字符按空格分隔放到一个主结构体中
    //然后遍历这个数组，看看是否是管道命令或者重定向命令
    //解析这个参数字符串，将参数单独提取出来
    char* parameter = strdup(strtok(temp_cmdString," "));
    if(checkCmd(parameter) == -1){
        analyze_res.type = -1;
        return ;
    }
    //需要一个命令列表
    analyze_res.parameters[analyze_res.paracount++] = parameter;
    parameter = strtok(NULL," ");
    while(parameter){
        //将char * 转换成 string
        if(strcmp(parameter, "|") == 0){
            ispipe = 1;
            analyze_res.type = 1;
        }
        if(strcmp(parameter, ">") == 0){
            isredirect = 1;
            analyze_res.type = 2;
        }
        /*********
        *...
        *继续添加判断条件，判断输入重定向、错误输出重定向等等等等
        *********/
        analyze_res.parameters[analyze_res.paracount++] = strdup(parameter);
        parameter = strtok(NULL," ");
    }
    //管道指令和重定向不能同时出现
    if(ispipe == 1 && isredirect == 1){
        cout << "Error command" << endl;
        analyze_res.type = -1;
        return ;
    }
    analyze_res.parameters[analyze_res.paracount++] = strdup(cmdString);
    analyze_res.parameters[analyze_res.paracount] = NULL;//最后加一个NULL

    // cout << "输入的字符串解析完毕，该字符串类型" << analyze_res.type << endl;
    // cout << "输入的字符串解析完毕，该字符串参数个数" << analyze_res.paracount - 1 << endl;
    //解析输入字符串
    switch(analyze_res.type){
        case 1: analyze_PipeCmd(); break;
        case 2: analyze_RedirectCmd(); break;
    }
    return ;
}
//对管道命令字符串进行解析
void analyze_PipeCmd(){
    /**
    * input: cmdString，解析该命令将命令和参数存放到结构体中
    * output: cmdRes
    */    
    char *temp_cmdString = strdup(cmdString);
    //cout << temp_cmdString << endl;
    //cout << "分析管道命令" << endl;
    //先保存每条指令的字符串
    char * tempPipeCmds[10];
    char * tempPipeCmds1[10];
    //管道中总共有几条指令
    int pipeNum = 0;
    //开始解析
    char * perCmd = strtok(temp_cmdString, "|");
    while(perCmd){
        //cout << perCmd << endl;
        tempPipeCmds[pipeNum] = strdup(perCmd);
        tempPipeCmds1[pipeNum++] = strdup(perCmd);
        perCmd = strtok(NULL, "|");
    }
    if(pipeNum > MAX_PIPE_CMD){
        cout << "Much more pipe commands!" << endl;
        analyze_res.type = -1;
        return;
    }
    //下面对每条指令进行解析，并将结果存到res中
    for(int i = 0; i < pipeNum; i++){
        analyze_res.pipeCmds[analyze_res.cmdcount] = new cmdRes();
        //cout<<&res.pipeCmds[res.cmdcount]<<endl;
        struct cmdRes* cmd =  analyze_res.pipeCmds[analyze_res.cmdcount]; 
        char* perCmdPara = strdup(strtok(tempPipeCmds[i], " "));
        if(checkCmd(perCmdPara) == -1){
            analyze_res.type = -1;
            return ;
        }
        while(perCmdPara != NULL){
            cmd->parameters[cmd->paracount++] = strdup(perCmdPara);
            perCmdPara = strtok(NULL, " ");
        }
        //保持和普通命令一致，管道命令将次换成管道标识即可
        cmd->parameters[cmd->paracount++] = strdup(tempPipeCmds1[i]);
        cmd->parameters[cmd->paracount] = NULL;
        analyze_res.cmdcount++;
    }
    //解析完毕，查看结果
    // cout << "分析管道结束,共有管道命令" << analyze_res.cmdcount << "条" << endl;
    // for(int i = 0; i < analyze_res.cmdcount; i++){
    //     for(int j = 0; j < (analyze_res.pipeCmds[i]) -> paracount; j++){
    //         //cout<<i<<":"<<j<<"  ";
    //         cout <<  (analyze_res.pipeCmds[i]) -> parameters[j] << "\t";
    //     }cout << endl;
    // }
}
//对重定向命令字符串进行解析
void analyze_RedirectCmd(){
    /**
    * input: cmdString，解析该命令将命令和参数存放到结构体中
    * output: cmdRes
    */    
    char *temp_cmdString = strdup(cmdString);
    cout << temp_cmdString << endl;
    cout << "分析重定向命令" << endl;
    //先保存每条指令的字符串,只能是一次重定向，且是 >
    //开始解析
    //这个是命令
    char *cmd = strdup(strtok(temp_cmdString, ">"));
    //cout << cmd << endl;
    //这个是重定向路径
    char *path = strdup(strtok(NULL, ">"));
    string trimpath = path;
    trimpath = trimpath.substr(1, trimpath.length()-1);//去掉空格
    //out << trimpath << endl;
    for(int i = 0; i < trimpath.length(); i++){
        path[i] = trimpath[i];
    }
    path[trimpath.length()] = '\0';
    //下面对指令进行解析，并将结果覆盖之前的结果存到analyze_res中
    //一个方法是将paracount - 2,并将后面置空
    analyze_res.parameters[analyze_res.paracount - 3] = cmd;
    analyze_res.parameters[analyze_res.paracount - 2] = NULL;
    analyze_res.paracount -= 2;
    analyze_res.redirectPath = path;
    //解析完毕，查看结果
    // cout << "分析重定向命令结束,重定向的命令为" << endl;
    // for(int i = 0; i < analyze_res.paracount; i++){
    //     cout << analyze_res.parameters[i] << "\t";
    // }cout << endl;
    cout << "分析重定向命令结束,重定向路径为" << analyze_res.redirectPath << endl;
}
//执行普通命令
void excute_OrdinaryCmd(){
    /**
    * input: cmdRes
    * output: execute ordinary command
    */   
    //这里有个分支，区分history命令，区分cd命令
    if(strcmp(analyze_res.parameters[0], "history") == 0){
        vector<string> history = get_History();
        //显示历史记录，显示个数为SHOW_HISTORY_NUM
        if(history.size() >= SHOW_HISTORY_NUM){
            for(int i = history.size() - SHOW_HISTORY_NUM; i < history.size(); i++){
                cout << i << " " << history[i] << endl;
            }   
        }else{
            for(int i = 0; i < history.size(); i++){
                cout << i << " " << history[i] << endl;
            }
        } 
        return ;
    }else if(strcmp(analyze_res.parameters[0], "cd") == 0){
        change_dir(analyze_res.parameters[1]);
        return ;
    }
    pid_t pid;
    while((pid = fork()) < 0);
    if(pid > 0){
        //父进程，等待子进程执行完毕
        wait(0);
    }else if(pid == 0){
        //子进程
        char* cmdPath = new char[MAX_LINE];
        strcpy(cmdPath, CMD_PATH);
        strcat(cmdPath, analyze_res.parameters[0]);
        //传进去之后，第一个参数是命令，第二个参数是参数字符串，最后一个是输入的字符串
        execvp(cmdPath, analyze_res.parameters);
        perror("exec error");
        exit(0);
    }
}
//执行管道命令
void excute_PipeCmd(){
    char pipeId[2];
    int fd[MAX_PIPE_CMD][2];
    //命令1和命令2 共享管道0，以此类推
    //将管道的id保存下来即可
    int n = analyze_res.cmdcount;
    //cout << "总共" << n << "条命令" << endl;
    for(int i = 1; i < n; i++){
        //cout << "打开管道" << i-1 << endl;
        pipe(fd[i - 1]);//open pipe
        //cout << fd[i-1][0] << fd[i-1][1] << endl;
        pipeId[0] = fd[i - 1][0] - '0';//在命令里面
        pipeId[1] = '\0';//结束标志
        //修改命令为管道，并添加管道号
        // ls    -l    -l    pipe   des  NULL    5
        int pc = (analyze_res.pipeCmds[i]) -> paracount;
        strcpy((analyze_res.pipeCmds[i]) -> parameters[pc-1], "pipe");
        (analyze_res.pipeCmds[i]) -> parameters[pc++] = strdup(pipeId);
        (analyze_res.pipeCmds[i]) -> parameters[pc] = NULL;
        (analyze_res.pipeCmds[i]) -> paracount = pc;
        // cout <<"参数个数为"<<(analyze_res.pipeCmds[i]) -> paracount<<endl;
        // for(int para = 0; para < (analyze_res.pipeCmds[i]) -> paracount; para++){
        //     cout << (analyze_res.pipeCmds[i]) -> parameters[para] << "\t";
        // }cout<<endl;
    }
    //执行路径
    char* cmdPath = new char[MAX_LINE];
    strcpy(cmdPath, CMD_PATH);
    //这里先执行第一条，因为要将标准输出转换为管道输入
    //cout << "将标准输出改成管道输入" << endl;
    dup2(1, 99);//将所有输出写到标准输出, 将99定为标准输出
    dup2(fd[0][1], 1);//第一个命令的标准输出写入管道中
    //1 管道
    pid_t p1;
    while((p1 = fork()) == -1);
    if(p1 == 0){
        //执行第一条命令
        //cout << "执行第一条命令" << endl;
        strcat(cmdPath, (analyze_res.pipeCmds[0]) -> parameters[0]);
        //传进去之后，第一个参数是命令，第二个参数是参数字符串，最后一个是输入的字符串
        // for(int para = 0; para < (analyze_res.pipeCmds[0]) -> paracount; para++){
        //     cout << (analyze_res.pipeCmds[0]) -> parameters[para] << endl;
        // }
        execvp(cmdPath, (analyze_res.pipeCmds[0]) -> parameters);
        perror("exec error");
        exit(0);
    }else{
        //等待第一条执行完毕
        wait(0);
        //cout << "执行第一条命令结束" << endl;
        pid_t p2;
        while((p2 = fork()) == -1);
        if(p2 == 0){
            //这里先执行第二条到倒数第二条，只需要从管道读出数据处理即可
            if(n > 2){
                //如果大于两条就需要执行
                for(int i = 1;i < n - 1;i++){
                    cout << "执行第" << i+1 << "条命令" << endl;
                    //标准输出写道管道中
                    dup2(fd[i][1], 1);
                    //perror("err");
                    strcat(cmdPath, (analyze_res.pipeCmds[i]) -> parameters[0]);
                    // for(int para = 0; para < (analyze_res.pipeCmds[i]) -> paracount; para++){
                    //     cout << (analyze_res.pipeCmds[i]) -> parameters[para] << endl;
                    // }
                    execvp(cmdPath, (analyze_res.pipeCmds[i]) -> parameters);
                }
            }
            //执行完毕退出，执行最后一条
            exit(0);
        }else{
            wait(0);
            //将标准输出从99转到1，并关闭99
            dup2(99, 1);
            close(99);
            //cout << "执行最后一条命令" << endl;
            pid_t p3;
            while((p2 = fork()) == -1);
            if(p2 == 0){
                strcat(cmdPath, (analyze_res.pipeCmds[n - 1]) -> parameters[0]);
                // for(int para = 0; para < (analyze_res.pipeCmds[n - 1]) -> paracount; para++){
                //     cout << (analyze_res.pipeCmds[n - 1]) -> parameters[para] << endl;
                // }
                execvp(cmdPath, (analyze_res.pipeCmds[n - 1]) -> parameters);
            }else{
                wait(0);
            }
        }
    }
    return ;
}
//执行重定向命令
void excute_RedirectCmd(){
    /**
    * input: cmdRes
    * output: execute ordinary command
    */   
    //int dup2(int oldfd, int newfd);//将newfd指向的文件指向到oldfd指向的文件
    fflush(stdout);//刷新缓冲区
    pid_t pid;
    while((pid = fork()) < 0);
    if(pid > 0){
        //父进程，等待子进程执行完毕
        wait(0);
    }else if(pid == 0){
        //子进程
        char* cmdPath = new char[MAX_LINE];
        strcpy(cmdPath, CMD_PATH);
        strcat(cmdPath, analyze_res.parameters[0]);
	    int fd = open(analyze_res.redirectPath, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        dup2(fd,1);//将标准输出重定向到文件
        //目前仅支持一次重定向
		//int fd=open(retptr,O_WRONLY|O_CREAT|O_APPEND,0664);
        execvp(cmdPath, analyze_res.parameters);
		perror("exec error");
		exit(0);
    }
}
//检查命令是否存在
int checkCmd(char * cmd){
    if(strcmp(cmd, "ls") == 0){
        return 1;
    }else if(strcmp(cmd, "echo") == 0){
        return 1;
    }else if(strcmp(cmd, "cat") == 0){
        return 1;
    }else if(strcmp(cmd, "mkdir") == 0){
        return 1;
    }else if(strcmp(cmd, "rmdir") == 0){
        return 1;
    }else if(strcmp(cmd, "touch") == 0){
        return 1;
    }else if(strcmp(cmd, "rm") == 0){
        return 1;
    }else if(strcmp(cmd, "cd") == 0){
        return 1;
    }else if(strcmp(cmd, "pwd") == 0){
        return 1;
    }else if(strcmp(cmd, "wc") == 0){
        return 1;
    }else if(strcmp(cmd, "grep") == 0){
        return 1;
    }else if(strcmp(cmd, "clear") == 0){
        return 1;
    }else if(strcmp(cmd, "head") == 0){
        return 1;
    }else if(strcmp(cmd, "help") == 0){
        return 1;
    }else if(strcmp(cmd, "history") == 0){
        return 1;
    }else if(strcmp(cmd, "RRbin") == 0){
        return 1;
    }else if(strcmp(cmd, "test") == 0){
        return 1;
    }else {
        return -1;
    }
     
    return 1;
}
//获取历史命令列表
vector<string> get_History(){
    string filename="history";
    ifstream in(filename);
    vector<string> lines;
    string line;
    if(in){//有该文件
        while(getline(in,line)){
            //line中不包括每行的换行符
            lines.push_back(line);
        }  
    }  
    else{//没有该文件
        cout << "no such file" << endl;  
    }
    return lines;
}

