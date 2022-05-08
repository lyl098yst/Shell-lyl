#include "help.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc < 2){
        cout << "Too few parameters" << endl;
        return 0;
    }else if(argc == 2){
        showHelpAll();
        return 0;
    }else if(argc >= 4){
        cout << "Too many parameters" << endl;
        return 0;
    }
    char helpCmd[10];
    strcpy(helpCmd, argv[1]);
    if(strcmp(helpCmd, "cat"    ) == 0) { showcat();     return 0;}
    if(strcmp(helpCmd, "cd"     ) == 0) { showcd();      return 0;}
    if(strcmp(helpCmd, "clear"  ) == 0) { showclear();   return 0;}
    if(strcmp(helpCmd, "echo"   ) == 0) { showecho();    return 0;}
    if(strcmp(helpCmd, "grep"   ) == 0) { showgrep();    return 0;}
    if(strcmp(helpCmd, "head"   ) == 0) { showhead();    return 0;}
    if(strcmp(helpCmd, "help"   ) == 0) { showhelp();    return 0;}
    if(strcmp(helpCmd, "ls"     ) == 0) { showls();      return 0;}
    if(strcmp(helpCmd, "mkdir"  ) == 0) { showmkdir();   return 0;}
    if(strcmp(helpCmd, "pwd"    ) == 0) { showpwd();     return 0;}
    if(strcmp(helpCmd, "rm"     ) == 0) { showrm();      return 0;}
    if(strcmp(helpCmd, "rmdir"  ) == 0) { showrmdir();   return 0;}
    if(strcmp(helpCmd, "touch"  ) == 0) { showtouch();   return 0;}
    if(strcmp(helpCmd, "wc"     ) == 0) { showwc();      return 0;}
    if(strcmp(helpCmd, "exit"   ) == 0) { showexit();    return 0;}
    if(strcmp(helpCmd, "history") == 0) { showhistory(); return 0;}
    return 0;
}

void showcat(){
    cout << "cat: 用于显示文件内容" <<endl;
    cout << "\t参数: [文件名称] | None" <<endl;
    cout << "\t用法1: cat a.cpp 显示a.cpp文件内容" <<endl;
    cout << "\t用法2: cat 从标准输入读取数据并显示，输入exit退出" <<endl;
}
void showcd(){
    cout << "cd: 用于切换工作路径" <<endl;
    cout << "\t参数: [工作路径]" <<endl;
    cout << "\t用法: cd source 切换到source目录下" <<endl;
}
void showclear(){
    cout << "clear: 用于清空标准输出" <<endl;
    cout << "\t参数: None" <<endl;
    cout << "\t用法: clear 清空标准输出的内容" <<endl;
}
void showecho(){
    cout << "echo: 用于信息回显" <<endl;
    cout << "\t参数: [回显信息] | None" <<endl;
    cout << "\t用法1: echo 'hello' 'world' 显示hello world" <<endl;
    cout << "\t用法2: echo 从标准输入读取数据并显示，输入exit退出" <<endl;
}
void showgrep(){
    cout << "grep: 用于查找文件里符合条件的字符串" <<endl;
    cout << "\t参数: [文件名] [字符串]" <<endl;
    cout << "\t用法: grep a.cpp printf 显示a.cpp中包含printf的行" <<endl;
    cout << "\t管道用法: ls -l | grep cpp 显示ls中包含cpp的行" <<endl;
}
void showhead(){
    cout << "head: 用于显示文件的前n行" <<endl;
    cout << "\t参数: [文件名] [行数] | None" <<endl;
    cout << "\t用法1: head -5 a.cpp 显示a.cpp的前5行" <<endl;
    cout << "\t用法2: head a.cpp 默认显示a.cpp的前10行" <<endl;
    cout << "\t管道用法: ls -l | head -3 显示ls结果的前3行" <<endl;
}
void showhelp(){
    cout << "help: 用于显示命令帮助" <<endl;
    cout << "\t参数: [命令] | None" <<endl;
    cout << "\t用法1: help 显示所有命令的使用手册" <<endl;
    cout << "\t用法2: help -ls 显示ls命令的使用手册" <<endl;
}
void showls(){
    cout << "ls: 用于查看文件信息" <<endl;
    cout << "\t参数: [-a | -i | -l | -n | -q | -r]" <<endl;
    cout << "\t用法1: ls -a 显示当前目录下所有文件的文件名" <<endl;
    cout << "\t用法2: ls -i 显示文件节点号和文件名称" <<endl;
    cout << "\t用法3: ls -l 显示文件型态、权限、拥有者、文件大小、文件名等信息" <<endl;
    cout << "\t用法4: ls -n 显示当前目录下文件总数" <<endl;
    cout << "\t用法5: ls -q 显示的文件按字母序从小到大排序" <<endl;
    cout << "\t用法6: ls -r 显示的文件按字母序从大到小排序" <<endl;
    cout << "\t用法7: ls 后面跟多个参数混合使用，如 ls -l -i -q" <<endl;
}
void showmkdir(){
    cout << "mkdir: 用于创建目录文件" <<endl;
    cout << "\t参数: [目录名]" <<endl;
    cout << "\t用法: mkdir dir 创建一个目录，名字为dir" <<endl;
    cout << "\t注: 使用mkdir创建的是目录，需要用rmdir进行删除" <<endl;
}
void showpwd(){
    cout << "pwd: 用于显示当前工作路径" <<endl;
    cout << "\t参数: None" <<endl;
    cout << "\t用法: pwd 显示当前工作路径" <<endl;
}
void showrm(){
    cout << "rm: 用于删除文件" <<endl;
    cout << "\t参数: [文件名]" <<endl;
    cout << "\t用法: rm a.cpp 删除名字为a.cpp的文件" <<endl;
    cout << "\t注: rm 只可用于删除文件" <<endl;
}
void showrmdir(){
    cout << "rmdir: 用于删除目录" <<endl;
    cout << "\t参数: [目录名]" <<endl;
    cout << "\t用法: rmdir dir 删除名字为dir的目录" <<endl;
    cout << "\t注: rmdir 只可用于删除目录" <<endl;
}
void showtouch(){
    cout << "touch: 用于创建文件" <<endl;
    cout << "\t参数: [文件名]" <<endl;
    cout << "\t用法: touch a.cpp 创建一个文件，名字为a.cpp" <<endl;
    cout << "\t注: 使用touch创建的是文件，需要用rm进行删除" <<endl;
}
void showwc(){
    cout << "wc: 用于对文件统计字数和行数" <<endl;
    cout << "\t参数: [文件名]" <<endl;
    cout << "\t用法: wc a.cpp 显示a.cpp的文件名、字数和行数" << endl;
    cout << "\t管道用法: ls -l | wc 显示ls结果的行数" << endl;
}
void showhistory(){
    cout << "history: 用于显示历史输入命令" <<endl;
    cout << "\t参数: Nonde" <<endl;
    cout << "\t用法1: history 显示历史命令输入" << endl;
    cout << "\t用法2: !! 用于执行上一条执行过的命令" << endl;
    cout << "\t用法3: !** 用于执行上一条以**开头的命令" << endl;
    cout << "\t用法4: !n 用于执行历史记录中第n条命令" << endl;
}
void showexit(){
    cout << "exit: 用于退出shell" <<endl;
    cout << "\t参数: None" <<endl;
    cout << "\t用法: exit 退出shell" << endl;
}
void showNone(){
    cout << "命令输入错误，请重新输入！" <<endl;
};
void showHelpAll(){
    showclear();
    showcat();
    showecho(); 
    showcd();
    showpwd();
    showls(); 
    showhead();
    showgrep();
    showwc(); 
    showmkdir();
    showrmdir();
    showtouch();
    showrm(); 
    showhelp();
    showhistory();
    showexit();
}
