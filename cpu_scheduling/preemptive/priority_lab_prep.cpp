#include<bits/stdc++.h>
using namespace std;

struct process {
    int burst_time;
    int burst;
    int priority;
    int arrival;
    int start;
    int end;
    int index;
    int turn;
    int wait;
};


bool compare2(process p1, process p2)
{
    return (p1.arrival<p2.arrival) || (p1.arrival==p2.arrival && p1.burst_time<p2.burst_time);
}

int main() {
    int num;
    cout << "Enter number of processes\n";
    cin >> num;
    process processes[num];

    cout << "Enter burst time and priority for each process\n";
    for(int i=0; i<num; i++) {
        cin >> processes[i].burst_time >> processes[i].priority>>processes[i].arrival;
        processes[i].burst = processes[i].burst_time;
        processes[i].index = i;
    }
    
    sort(processes, processes+num, compare2);
    int curr=0, done=0,prev=-1;
    vector<int>ready;
    while(done<num)
    {
        for(int i=0; i<num; i++)
        {
            if(processes[i].arrival<=curr && processes[i].burst>0)
            ready.push_back(processes[i].index);
        }
        if(ready.size()==0)
        {
            curr++;
            continue;
        }
        int mx_priority=INT_MIN,idx;
        process temp;
        for(int i=0; i<ready.size(); i++)
        {
            if(mx_priority<processes[ready[i]].priority)
            {
                mx_priority = processes[ready[i]].priority;
                idx = ready[i];
            }
        }
        if(idx!=prev)
        cout<<" |- -P"<<processes[idx].index+1<<" ";
        else
        cout<<" - ";
        processes[idx].burst--;
        curr++;
        prev = idx;
        if(processes[idx].burst==0)
        {
            processes[idx].end = curr;
            done++;
            ready.erase(remove(ready.begin(), ready.end(), idx), ready.end());
        }
    }
    cout<<" | "<<endl;
    for(int i=0; i<num; i++)
    {
        processes[i].turn = processes[i].end - processes[i].arrival;
        processes[i].wait = processes[i].turn - processes[i].burst_time;
    }
    
    // cout<<"Gantt Chart\n";

    // for(int i = 0; i < num; i++) {
    //     for(int j = processes[i].start; j < processes[i].end; j++) {
    //         if(j == processes[i].start)
    //             cout << "| ";
    //         else if(j == (processes[i].end - processes[i].start) / 2 + processes[i].start)
    //             cout << "P" << processes[i].index;
    //         else
    //             cout << "-";
    //     }
    //     if(processes[i].end - processes[i].start <= 1)
    //         cout << "P" << processes[i].index;
    // }
    // cout << "|";
    // cout << endl;

    // for(int i=0; i<num; i++)
    // {
    //     for(int j=processes[i].start; j<processes[i].end; j++)
    //     {
    //         if(j==processes[i].start)
    //             cout<<j<<" ";
    //         else
    //         cout<<" ";
    //     }
    // }
    // cout<<processes[num-1].end<<endl;

    cout<<"Turnaround and Waiting times: \n";
    for(auto x : processes)
    {
        cout<<"P"<<x.index<<" Turn: "<<x.turn<<" Wait: "<<x.wait<<endl;
    }

    int sum=0;
    cout<<"Average Turn Around Time: \n";
    for(auto x : processes)
    sum+=x.turn;
    cout<<(double)sum/num<<endl;

    sum=0;
    cout<<"Average Waiting Time: \n";
    for(auto x : processes)
    sum+=x.wait;
    cout<<(double)sum/num<<endl;
    return 0;
}