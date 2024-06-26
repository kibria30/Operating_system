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

int total_task;
Task task[100];
queue<Task> waiting;
queue<Task> ready;
queue<Chart> running;

bool compare(const Task &a, const Task &b) {
    return a.arival < b.arival;
}

void readInput(){
    cin>>total_task;
    for(int i=0; i<total_task; i++){
        cin>>task[i].pid>>task[i].arival>>task[i].burst;
    }
}

void showTask(Task X[]){
    for(int i=0; i<total_task; i++){
        cout<<task[i].pid<<" "<<task[i].arival<<" "<<task[i].burst<<" "<<task[i].completion<<" "<<endl;
    }
    cout<<endl;
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

void calculateTimes(){
    for(int i=0; i<total_task; i++){
        task[i].turnaround = task[i].completion - task[i].arival;
        task[i].wait = task[i].turnaround - task[i].burst;
    } 
}

void printTable(){
    cout<<"Process\t\t"<<"Burst_time\t"<<"Turnaround_Time\t\t"<<"Waiting_Time\t"<<endl;
    for(int i=0; i<total_task; i++){
        cout<<task[i].pid<<"\t\t"<<task[i].burst<<"\t\t"<<task[i].turnaround<<"\t\t\t"<<task[i].wait<<endl;
    }
}

void printAvgTimes(){
    int total_turn_time = 0;
    int total_wait_time = 0;
    for(int i=0; i<total_task; i++){
        total_turn_time += task[i].turnaround;
        total_wait_time += task[i].wait;
    }

    cout<<"Average turnaround time: "<<(float)total_turn_time/total_task<<endl;
    cout<<"Average waiting time: "<<(float)total_wait_time/total_task<<endl;
}

void updateTimes(string pid, int completion){
    for(int i=0; i<total_task; i++){
        if(task[i].pid == pid){
            task[i].completion = completion;
        }
    }
}

void roundRobin(int quantum){
    int clk = 0;
    Task processing = waiting.front();
    waiting.pop();
    do{
        int runtime = quantum;
        for(int j=0; j<=quantum; j++){
            
            while(!waiting.empty() && waiting.front().arival == clk){
                //cout<<waiting.front().pid<<"-clk:"<<clk<<endl;
                ready.push(waiting.front());
                waiting.pop();
            };
            if(j!=0){
                
                cout<<processing.pid<<" ";
                clk++;

            }

            //cout<<processing.pid<<"-burst: "<<processing.burst<<endl;
            if(processing.burst-j==0){
                //cout<<processing.pid<<"-"<<clk<<"  ";
                // processing = ready.front();
                // ready.pop();
                updateTimes(processing.pid, clk);
                runtime = j;
                break;
            }
        }
        if(processing.burst-runtime != 0){
            processing.burst -= runtime;
            //cout<<processing.pid<<" ";
            ready.push(processing);
            processing = ready.front();
            ready.pop();
        }else{
            
            processing = ready.front();
            ready.pop();
        }
    }while(!ready.empty() || !waiting.empty());
    clk++;
    updateTimes(processing.pid, clk);
    cout<<processing.pid<<endl;
}

int main(){
    freopen("rr_input.txt", "r", stdin);
    readInput();
    showTask(task);
    sort(task, task+total_task, compare);
    showTask(task);
    for(int i=0; i<total_task; i++){
        waiting.push(task[i]);
    }

    int quantum = 2;
    roundRobin(quantum);
    
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
    calculateTimes();
    printTable();
    printAvgTimes();
    showTask(task);
}