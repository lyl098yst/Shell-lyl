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
using namespace std;
#define MAX_PWD_LENGTH 1024
char dir[MAX_PWD_LENGTH];