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

    bool operator<(const Task& other) const {
        // Customize the comparison based on requirements
        return priority > other.priority;
    }
};

// struct Chart{
//     int start;
//     string pid;
//     int finish;
// };

int total_task;
Task task[100];
priority_queue< pair<int, Task>, vector< pair<int, Task>>, greater < pair<int, Task>>> wait;
priority_queue< pair<int, Task>> ready;

void readInput(){
    cin>>total_task;
    for(int i=0; i<total_task; i++){
        cin>>task[i].pid>>task[i].burst>>task[i].priority>>task[i].arival;
    }
}

void showTask(Task X[]){
    cout<<"PID\t"<<"burst\t"<<"priority\t"<<"arival\t"<<"completion"<<endl; 
    for(int i=0; i<total_task; i++){
        cout<<X[i].pid<<"\t"<<X[i].burst<<"\t"<<X[i].priority<<"\t\t"<<X[i].arival<<"\t"<<X[i].completion<<endl;
    }
    cout<<endl;
}

void insertCompletTime(string pid, int CT){
    for(int i=0; i<total_task; i++){
        if(task[i].pid == pid){
            task[i].completion = CT;
        }
    }
}

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

int main(){
    freopen("tasks_2.txt", "r", stdin);
    readInput();
    showTask(task);

    for(int i=0; i<total_task; i++){
        wait.push(make_pair(task[i].arival, task[i]));
    }

    ready.push(make_pair(wait.top().second.priority, wait.top().second));
    wait.pop();
    Task current = ready.top().second, temp, temp2;
    ready.pop();
    //cout<<current.pid;

    int time=current.arival, start=current.arival ;
    cout<<0;
    while(!wait.empty() || !ready.empty()){
        while(!wait.empty() && time == wait.top().first){
            ready.push(make_pair(wait.top().second.priority, wait.top().second));
            wait.pop();
        }

        // if(ready.empty()){
        //     cout<<"time-"<<time<<endl;
        //     // time++;
        //     // continue;
        // }

        if(ready.top().second.priority>current.priority){
            temp = current;
            cout<<"|----"<<current.pid<<"----|"<<time;
            current = ready.top().second;
            ready.pop();
            temp.burst = temp.burst-(time-start);
            ready.push(make_pair(temp.burst-(time-start), temp));
            start = time;
        }else if(time-start == current.burst){
            insertCompletTime(current.pid, time);
            cout<<"|----"<<current.pid<<"----|"<<start+current.burst;
            current = ready.top().second;
            ready.pop();
            start = time;
        }
        time++;
    }
    
    insertCompletTime(current.pid, time+current.burst-(time-start));
    cout<<"|---"<<current.pid<<"---|"<<time+current.burst-(time-start)<<endl;

    cout<<endl;
    showTask(task);
    calculateTimes();
    printTable();
    printAvgTimes();
    
}