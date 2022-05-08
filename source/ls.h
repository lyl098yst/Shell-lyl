#include "../color.cpp"
#include <iostream>
#include <unistd.h>
#include <readline/readline.h>
#include <dirent.h>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#define END " "
using namespace std;

enum parameter{
    para_a, para_i, para_l, para_n, para_q, para_r
}; 

struct file{
    string name;
    int type;
    struct stat detail;
};
vector<file>files;
bool parameters[30];

int get_File_Info();
void print_File_Info();
void print_File_Name(struct file& file);
string get_Permission(mode_t mode);