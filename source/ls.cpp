/***************************
** author: lyl
** time: 5/6/2021
** version: v1
** function: ls命令
**************************/

#include "ls.h" 
using namespace std;

int main(int argc, char *argv[]){
    
    //将参数列表清空
    memset(parameters, false, sizeof(parameters));
    //遍历获取参数，需判断是否有参数传进来
    if(argc>=2){
        for(int i = 1; i < argc - 1; i++){
            string para = argv[i];
            for(int j = 0; j < para.length(); j++)
            switch(para[j]){
                case '-': break;
                case 'a': parameters[para_a] = true; break;
                case 'i': parameters[para_i] = true; break;
                case 'l': parameters[para_l] = true; break;
                case 'n': parameters[para_n] = true; break;
                case 'q': parameters[para_q] = true; break;
                case 'r': parameters[para_r] = true; break;  
                default : cout << "Unvalid parameter!" << endl; return 0;
            }
        }
    }
    //思路：获取所有的信息，根据参数的不同打印
    if(get_File_Info() == -1){
        cout << "Fail to get files infomation" << endl;
        return 0;
    }
    //获取信息之后打印即可
    print_File_Info();
   
    return 0;
}

int get_File_Info(){
    /**
    * input: None
    * output: files 存放文件信息的结构体
    */    
    //打开一个目录流，读取所有的文件
    DIR *dir;
    if((dir = opendir(".")) == NULL){
        perror("error");    
        return -1;
    }
    //可在头文件中查看定义，存放文件简略信息
    struct dirent *rent;
    //一个文件一个文件读,并存放信息到结构体中
    while((rent = readdir(dir))){
        //这里判断-a参数
        if(!parameters[para_a] && rent->d_name[0] == '.' ){
            continue;
        } 
        //构建一个文件结构体
        struct file oneFile;
        //将信息加入进去
        oneFile.name = rent->d_name;
        oneFile.type = int(rent->d_type);
        //获取文件详细信息并汇总到文件结构体file中
        struct stat fileDetail;
        int result = stat(rent->d_name, &fileDetail);
        if(result == -1){
            perror("error:");
            return -1;
        }
        oneFile.detail = fileDetail;
        //存入文件列表
        files.push_back(oneFile);
    } 
    closedir(dir);//关闭目录流
    //这里判断-q 和 -r参数
    if(parameters[para_q]){
        sort(files.begin(), files.end(), [](file &f1, file &f2){
            return f1.name < f2.name;
        });
    }else if(parameters[para_r]){
        sort(files.begin(), files.end(), [](file &f1, file &f2){
            return f1.name > f2.name;
        });
    }
    return 1;
}

void print_File_Info(){
    /**
    * input: files 存放文件信息的结构体
    * output: 显示文件信息
    */
    //打印总计(total) 
    cout << "total " << files.size() <<endl;
    for(int i = 0; i < files.size(); i++){
        if(parameters[para_i]){
            cout << files[i].detail.st_ino << END;
        }
        if(parameters[para_l] || parameters[para_n]){
            //文件属性字段
            cout << get_Permission(files[i].detail.st_mode) << END;
            cout << files[i].detail.st_nlink << END;
            if(parameters[para_n]){
                //文件用户id
                cout << files[i].detail.st_uid << END;
                //文件用户组id
                cout << files[i].detail.st_gid << END;
            }else if(parameters[para_l]){
                //文件（目录）拥有者
                cout << (*getpwuid(files[i].detail.st_uid)).pw_name << END;
                //文件（目录）拥有者所在的组
                cout << (*getgrgid(files[i].detail.st_gid)).gr_name << END;
            }
            //文件所占用的空间(以字节为单位)
            cout << files[i].detail.st_size << END;
            //文件（目录）最近访问（修改）时间
            cout << string(ctime(&(files[i].detail.st_mtime))).substr(0,16) << END;
        }
        //文件名
        print_File_Name(files[i]);
        if(parameters[para_l] || parameters[para_n] || parameters[para_i]){
            cout << endl;
        }
    }
    cout << endl;
}

void print_File_Name(struct file& file){
    /**
    * input: file 文件结构体
    * output: 输出文件的名字，带颜色
    */
    switch(file.type){
        case 4:
            //目录
            cout << BLUE << file.name << RESET << "\t";
            break;
        case 8:
            //普通文件
            cout << GREEN << file.name << RESET << "\t";
            break;
        default:
            cout << WHITE << file.name << RESET << "\t";
            break;
    }
}

//mode_t = unsigned short 实际上也就是一种无符号整数。
//另外struct stat 定义中的 st_mode 成员变量也是使用的 mode_t 类型的变量。
string get_Permission(mode_t mode){
    /**
    * input: mode_t mode, string &str
    * output: 获取文件的权限存放到str中
    */
    string str("----------");
    if(S_ISDIR(mode))  str[0] = 'd'; //目录
    if(S_ISCHR(mode))  str[0] = 'c'; //字符设备文件
    if(S_ISBLK(mode))  str[0] = 'b'; //块设备文件
    if(S_ISFIFO(mode)) str[0] = 'p'; //有名管道
    if(S_ISLNK(mode))  str[0] = 'l'; //连接文件
    if(S_ISSOCK(mode)) str[0] = 's'; //套接字类型

    if(S_IRUSR & mode) str[1] = 'r'; //读
    if(S_IWUSR & mode) str[2] = 'w'; //写
    if(S_IXUSR & mode) str[3] = 'x'; //执行

    if(S_IRGRP & mode) str[4] = 'r'; //读
    if(S_IWGRP & mode) str[5] = 'w'; //写
    if(S_IXGRP & mode) str[6] = 'x'; //执行

    if(S_IROTH & mode) str[7] = 'r'; //读
    if(S_IWOTH & mode) str[8] = 'w'; //写
    if(S_IXOTH & mode) str[9] = 'x'; //执行
    return str;
}
