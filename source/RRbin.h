//
// Created by 魏子沄 on 2021/5/25.
//

#include <iostream>
#include <queue>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
#include "../color.cpp"
#include "../config.h"
//#define MAX 100
//#define PATH "/mnt/d/lyl/RR_data.txt" 
using namespace std;

//进程结构体
struct RR {
    string Name;        //进程名
    int ArrivalTime;  //到达时间
    int nextArrive;   //下一次可执行时间
    int ServiceTime;  //服务时间
    int pri;
    int NeededTime;   //所需时间
    int StartTime;    //开始执行时间
    int FinishedTime; //完成时间
    int WholeTime;    //周转时间
    double WeightWholeTime;  //带权周转时间
    bool operator < (const RR &a) const {
        if(nextArrive != a.nextArrive) {
            return nextArrive > a.nextArrive ;//最小值优先 
        }
        return pri > a.pri;
    }  
};
int ch;

vector<RR> pros;  //总进程列表，原始的信息

//vector<RR> exec;  //执行的进程队列，拷贝的一份
vector<RR> RRend ;  //完成的进程列表，输出结果需要

priority_queue<RR> Pqueue; //优先队列，按nextArrive从小到大

double AverageWT, AverageWWT;
int q = 2;  //时间片长度
int num_of_procs;  //进程个数

void clear_info();

void clear();

void input_file();

void initInfoOutput();

void input_manu();

void roundRobin();

RR input_One(bool running, int cur);

void change_len();

void show_one(RR pro);

void show_res();