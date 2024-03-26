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
Task ready[100];
Chart chart[100];

void readInput(){
    cin>>total_task;
    for(int i=0; i<total_task; i++){
        cin>>task[i].pid>>task[i].burst>>task[i].priority;// >>task[i].arival;
    }
}

void showTask(Task X[]){
    for(int i=0; i<total_task; i++){
        cout<<X[i].pid<<" "<<X[i].burst<<" "<<X[i].priority<<endl;
    }
    cout<<endl;
}

void printOutput(){
    for(int i=0; i<total_task; i++){
        cout<<"|---"<<chart[i].pid<<"---|";
    }
    cout<<endl<<0;
    for(int i=0; i<total_task; i++){
        if(chart[i].finish<10)
            cout<<"         "<<chart[i].finish;
        else
            cout<<"        "<<chart[i].finish;
    }
    cout<<endl;
}

void sort(){
    Task temp;
    for(int i=0; i<total_task-1; i++){
        for(int j=0; j<total_task-1-i; j++){
            if(ready[j].burst > ready[j+1].burst){
                temp = ready[j];
                ready[j] = ready[j+1];
                ready[j+1] = temp;
            }
        }
    }
}

void calculateTimes(){
    for(int i=0; i<total_task; i++){
        ready[i].turnaround = ready[i].completion - ready[i].arival;
        ready[i].wait = ready[i].turnaround - ready[i].burst;
    } 
}

void printTable(){
    cout<<"Process\t\t"<<"Burst_time\t"<<"Turnaround_Time\t\t"<<"Waiting_Time\t"<<endl;
    for(int i=0; i<total_task; i++){
        cout<<ready[i].pid<<"\t\t"<<ready[i].burst<<"\t\t"<<ready[i].turnaround<<"\t\t\t"<<ready[i].wait<<endl;
    }
}

void printAvgTimes(){
    int total_turn_time = 0;
    int total_wait_time = 0;
    for(int i=0; i<total_task; i++){
        total_turn_time += ready[i].turnaround;
        total_wait_time += ready[i].wait;
    }

    cout<<"Average turnaround time: "<<(float)total_turn_time/total_task<<endl;
    cout<<"Average waiting time: "<<(float)total_wait_time/total_task<<endl;
}

int main(){
    freopen("tasks.txt", "r", stdin);
    readInput();
    showTask(task);
    
    for(int i=0; i<total_task; i++){
        ready[i] = task[i];
    }
    
    sort();
    showTask(ready);

    for(int i=0; i<total_task; i++){
        if(i==0){
            chart[i].start = 0;
            chart[i].pid = ready[i].pid;
            chart[i].finish = chart[i].start + ready[i].burst;
            ready[i].completion = chart[i].finish;
        }
        else{
            chart[i].start = chart[i-1].finish;
            chart[i].pid = ready[i].pid;
            chart[i].finish = chart[i].start + ready[i].burst;
            ready[i].completion = chart[i].finish;
        }
    }
    printOutput();
    calculateTimes();
    printTable();
    printAvgTimes();
}