#include<bits/stdc++.h>
using namespace std;

struct Task{
    string pid;
    int arival;
    int burst;
    int priority;
    int completion;
    int turnaround;
    int wait;
};

struct Chart{
    int start;
    string pid;
    int finish;
};

int total_task, quantum;
Task task[100];
queue<Task> ready;
queue<Chart> running;

void readInput(){
    cin>>total_task;
    for(int i=0; i<total_task; i++){
        cin>>task[i].pid>>task[i].arival>>task[i].burst;
    }
}

void showTask(Task X[]){
    for(int i=0; i<total_task; i++){
        cout<<task[i].pid<<" "<<task[i].arival<<" "<<task[i].burst<<endl;
    }
    cout<<endl;
}

void sort(){
    Task temp;
    for(int i=0; i<total_task-1; i++){
        for(int j=0; j<total_task-1-i; j++){
            if(task[j].arival > task[j+1].arival){
                temp = task[j];
                task[j] = task[j+1];
                task[j+1] = temp;
            }
        }
    }
}

// void printOutput(){
//     for(int i=0; i<total_task; i++){
//         cout<<"|---"<<chart[i].pid<<"---|";
//     }
//     cout<<endl<<0;
//     for(int i=0; i<total_task; i++){
//         if(chart[i].finish<10)
//             cout<<"         "<<chart[i].finish;
//         else
//             cout<<"        "<<chart[i].finish;
//     }
//     cout<<endl;
// }

// void calculateTimes(){
//     for(int i=0; i<total_task; i++){
//         ready[i].turnaround = ready[i].completion - ready[i].arival;
//         ready[i].wait = ready[i].turnaround - ready[i].burst;
//     } 
// }

// void printTable(){
//     cout<<"Process\t\t"<<"Burst_time\t"<<"Turnaround_Time\t\t"<<"Waiting_Time\t"<<endl;
//     for(int i=0; i<total_task; i++){
//         cout<<ready[i].pid<<"\t\t"<<ready[i].burst<<"\t\t"<<ready[i].turnaround<<"\t\t\t"<<ready[i].wait<<endl;
//     }
// }

// void printAvgTimes(){
//     int total_turn_time = 0;
//     int total_wait_time = 0;
//     for(int i=0; i<total_task; i++){
//         total_turn_time += ready[i].turnaround;
//         total_wait_time += ready[i].wait;
//     }

//     cout<<"Average turnaround time: "<<(float)total_turn_time/total_task<<endl;
//     cout<<"Average waiting time: "<<(float)total_wait_time/total_task<<endl;
// }

void roundRobin(){
    ready.push(task[0]);
    Chart selected;
    int selectReadyFrom=1;
    // selected.start = ready.front().arival;
    // selected.pid = ready.front().pid;
    // selected.finish = selected.start + quantum;
    // running.push(selected);

    while(!ready.empty()){        
        if(ready.front().burst<quantum){
            selected.start = ready.front().arival;
            selected.pid = ready.front().pid;
            selected.finish = selected.start + quantum;
            running.push(selected);
        }
        else{
            selected.start = ready.front().arival;
            selected.pid = ready.front().pid;
            selected.finish = selected.start + quantum;
            running.push(selected);
        }
        ready.pop();
        
        for(int i=selectReadyFrom; i<total_task; i++){
            if(task[i]. running.back().finish)
        }
    }
}

int main(){
    freopen("tasks_2.txt", "r", stdin);
    readInput();
    showTask(task);
    sort();
    showTask(task);
    quantum = 2;

    roundRobin();
    
    // for(int i=0; i<total_task; i++){
    //     ready[i] = task[i];
    // }

    // showTask(ready);

    // for(int i=0; i<total_task; i++){
    //     if(i==0){
    //         chart[i].start = 0;
    //         chart[i].pid = ready[i].pid;
    //         chart[i].finish = chart[i].start + ready[i].burst;
    //         ready[i].completion = chart[i].finish;
    //     }
    //     else{
    //         chart[i].start = chart[i-1].finish;
    //         chart[i].pid = ready[i].pid;
    //         chart[i].finish = chart[i].start + ready[i].burst;
    //         ready[i].completion = chart[i].finish;
    //     }
    // }
    // printOutput();
    // calculateTimes();
    // printTable();
    // printAvgTimes();
}