
//
// Created by 魏子沄 on 2021/5/25.
//

/***************************
** Changed by: 李宇龙
** time: 6/14/2021
** version: v2
** function: RRbin
**************************/
#include "RRbin.h"

//主函数
int main() {
    clear();
    cout << "Welcome to the simulator of the Round Robin! " << endl;
    while (1) {
        cout << GREEN << "********时间轮转算法************" << RESET << endl;
        cout << GREEN << "    功能1 - 读取文件进程信息"    << RESET << endl;
        cout << GREEN << "    功能2 - 手动输入添加进程"    << RESET << endl;
        cout << GREEN << "    功能3 - 查看已有进程信息"    << RESET << endl;
        cout << GREEN << "    功能4 - 清空已有进程信息"    << RESET << endl;
        cout << GREEN << "    功能5 - 修改时间片长度" << q << RESET << endl;
        cout << GREEN << "    功能6 - 执行轮转调度算法"    << RESET << endl;
        cout << GREEN << "    功能7 - 退出时间轮转算法"    << RESET << endl;
        cout << GREEN << "*******************************" << RESET << endl;
        cout << GREEN << "请输入功能序号：" << RESET;
        cin >> ch;
        while(ch > 7 || ch < 1){
            cout << RED << "序号错误，请重新输入序号：" << RESET;
            cin >> ch;
        }
        switch (ch) {
            case 1: input_file();     break;
            case 2: input_manu();     break;
            case 3: initInfoOutput(); break;
            case 4: clear_info();     break;
            case 5: change_len();     break;
            case 6: roundRobin();     break;
            case 7: clear(); exit(0);
        }
    }
}

//改变时间片长度
void change_len(){
    clear();
    cout << GREEN << "请输入时间片长度 (q > 0)：" << RESET;
    cin >> q;
    while ( q < 0 ){
        cout << RED << "时间片错误，请重新输入时间片 (q > 0)：" << RESET;
        cin >> q;
    }
    clear();
    cout << GREEN << "时间片长度修改为" << q << RESET << endl;;
}

//从文件读取数据
void input_file() {
    pros.clear();
    ifstream inData;
    try{
        inData.open(PATH);
        if (!inData) {
            cout << RED << "读取文件出错了！请检查文件是否存在！" << RESET << endl;
        } else {
            inData >> num_of_procs; // 进程个数
            //从RR_data.txt中读取各个进程的名称、到达时间和服务时间
            for (int i = 0; i < num_of_procs; i++) {
                RR temp;
                inData >> temp.Name;
                inData >> temp.ArrivalTime;
                inData >> temp.ServiceTime;
                pros.push_back(temp);
            }
        }
        inData.close();
        initInfoOutput();
    }catch(int e){
        inData.close();
        perror("err");
    }
    return;
}

//手动输入进程信息
void input_manu() {
    clear();
    cout << GREEN << "请输入要添加的进程数量 (1 - " << MAX << ")：" << RESET;
    cin >> num_of_procs;
    while ( num_of_procs < 1 || num_of_procs > MAX ){
        cout << RED << "数量错误，请重新输入进程数量 (1 - " << MAX << ")：" << RESET;
        cin >> num_of_procs;
    }
    for (int i = 0; i < num_of_procs; i++) {
        input_One(false, 0);
    }
    initInfoOutput();
    return ;
}

//输入信息界面
RR input_One(bool running, int cur){
    RR temp;
    cout << GREEN << "请输入添加第" << pros.size()+1 << "个进程的名称:" << RESET;
    cin >> temp.Name;
    if(!running){
        cout << GREEN << "请输入添加第" << pros.size()+1 << "个进程的到达时间:" << RESET;
        cin >> temp.ArrivalTime;
    }else{
        temp.ArrivalTime = cur;
    }
    cout << GREEN << "请输入添加第" << pros.size()+1 << "个进程的服务时间:" << RESET;
    cin >> temp.ServiceTime;
    temp.nextArrive = temp.ArrivalTime;
    temp.StartTime = -1;
    temp.pri = 1;
    temp.NeededTime = temp.ServiceTime;
    pros.push_back(temp);
    return temp;
}

//初始信息输出函数
void initInfoOutput() {
    clear();
    if( pros.size() == 0 ){
        cout << RED << "当前无进程，请先添加进程！" << RESET << endl;    
        return ;
    }
    cout << GREEN << "共读取" << pros.size() << "个进程，时间片长度为" << q << RESET <<endl;
    //输出用户所输入的信息
    cout << "所有进程的信息如下：" << endl;
    cout << "进程序号" << "\t";
    cout << "进程名称" << "\t";
    cout << "到达时间" << "\t";
    cout << "服务时间" << endl;
    for (int i = 0; i < pros.size(); i++) {
        cout << i+1 << "\t\t";
        show_one(pros[i]);
    }
}

//显示一个进程的信息
void show_one(RR pro){
    cout << pro.Name << "\t\t";
    cout << pro.ArrivalTime << "\t\t";
    cout << pro.ServiceTime << endl;
}

//显示结果信息
void show_res(){
    double x = 0, y = 0;
    for (int i = 0; i < RRend.size(); i++) {
        RRend[i].WholeTime = RRend[i].FinishedTime - RRend[i].ArrivalTime;
        RRend[i].WeightWholeTime = (double) RRend[i].WholeTime / RRend[i].ServiceTime;
        x += RRend[i].WholeTime;
        y += RRend[i].WeightWholeTime;
    }
    AverageWT = x / RRend.size();
    AverageWWT = y / RRend.size();

    cout << "*******************************" << endl;
    cout << "RR调度算法运行后：进程相关信息如下：" << endl;
    cout << "进程名称" << "\t";
    cout << "到达时间" << "\t";
    cout << "服务时间" << "\t";
    cout << "开始时间" << "\t";
    cout << "完成时间" << "\t";
    cout << "周转时间" << "\t";
    cout << "带权周转时间" << endl;
    for (int i = 0; i < RRend.size(); i++) {
        cout << RRend[i].Name << "\t\t"
             << RRend[i].ArrivalTime << "\t\t"
             << RRend[i].ServiceTime << "\t\t"
             << RRend[i].StartTime << "\t\t"
             << RRend[i].FinishedTime << "\t\t"
             << RRend[i].WholeTime << "\t\t"
             << RRend[i].WeightWholeTime << endl;
    }
    cout << "所有进程的平均周转时间 = " << AverageWT << endl;
    cout << "所有进程的平均带权周转时间 = " << AverageWWT << endl;
    cout << "*******************************" << endl;
}

//模拟函数_模拟调度算法过程
void roundRobin() {
    clear();
    if( pros.size() == 0 ){
        cout << RED << "当前无进程信息，请先输入信息！" << RESET << endl;    
        return ;
    }
    initInfoOutput();
    int CurrentTime = 0;  //当前时间
    int CPU_idle_time = 0; //CPU空闲时间为0
    RRend.clear();
    char flag, flag1;
    while (1) {
        cout << "请选择运行方式：单步运行 : t；全部运行 : a " << endl;
        cin >> flag;
        if (flag == 'a' || flag == 't') {
            break;
        }
    }
    //然后加入到队列中
    for (int i = 0; i < pros.size(); i++) {
        pros[i].NeededTime = pros[i].ServiceTime;//还需要多长时间
        pros[i].nextArrive = pros[i].ArrivalTime;//下一次可以运行的时间
        pros[i].StartTime = -1;//是否开始，若开始，开始时间是多少
        pros[i].pri = 1;
        Pqueue.push(pros[i]);
    }

    //当等待队列为空且总进程队列为空时，跳出循环
    while (!Pqueue.empty()) {
        if (flag == 't') {
            cout << GREEN << "请按p添加新进程，其余按键执行单步运行" << RESET <<endl;
            cin >> flag1;
            if (flag1 == 'p') {
                RR newR = input_One(true, CurrentTime);
                show_one(newR);
                Pqueue.push(newR);
            }
        }
        //取出第一个判断是否可以执行
        RR front = Pqueue.top();
        Pqueue.pop();
        if (front.nextArrive <= CurrentTime) {
            //如果可以运行则执行一个时间片
            //如果还没有执行过，修改第一次执行的时间
            if (front.StartTime == -1) {
                front.StartTime = CurrentTime;
            }
            if (front.NeededTime <= q) {
                //如果它还需要执行的时间小于一个时间片
                if(flag == 't'){
                    cout << setw(3) << CurrentTime << "时" << " -> " << setw(2) <<
                     CurrentTime + front.NeededTime << "时" << setw(3) <<
                     front.Name << endl;
                }
                CurrentTime += front.NeededTime;
                front.NeededTime = 0;
                front.FinishedTime = CurrentTime;
                RRend.push_back(front);
            } else {
                //如果它还需要执行的时间大于一个时间片
                if(flag == 't'){
                    cout << setw(3) << CurrentTime << "时" << " -> " << setw(2) <<
                        CurrentTime + q << "时" << setw(3) <<
                        front.Name << endl;
                }
                CurrentTime += q;
                front.NeededTime -= q;
                front.pri += 1;
                //仍然放到队尾
                front.nextArrive = CurrentTime;
                //cout << front.Name << ":"<< front.pri << ":" << front.nextArrive << endl;
                Pqueue.push(front);
            }
        } else {
            // 如果不能运行则还是放到队尾
            Pqueue.push(front);
            if(flag == 't'){
                cout << setw(3) << CurrentTime << "时" << " -> " << setw(2) <<
                        CurrentTime + 1 << "时" << setw(3) <<
                        "CPU空闲" << endl;
            }
            CurrentTime++;
            CPU_idle_time++;
        }
    }
    cout << "*******************************" << endl;
    cout << "RRbin执行完毕, CPU空闲率为" << setw(5) << (double)CPU_idle_time/CurrentTime * 100 << "%" << endl;
    cout << "RRbin执行完毕, CPU利用率为" << setw(5) << 100 - (double)CPU_idle_time/CurrentTime * 100 << "%" << endl;
    show_res();
}

//清屏函数
void clear(){
    fflush(stdout);
    printf("\033[H\033[2J");
}

//清空数据
void clear_info(){
    clear();
    pros.clear();
    num_of_procs = 0;
    cout << RED << "进程信息清除成功，运行算法前请先输入信息！" << RESET << endl;
}
