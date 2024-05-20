#include <bits/stdc++.h>
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
    int processed;
};

bool compare(process p1, process p2) {
    return p1.burst_time < p2.burst_time;
}

void gantt(vector<process>& processes, int l, int r, int id) {
    for (int i = l; i < r; i++) {
        if (i == l)
            cout << "| ";
        else if (i == (r - l) / 2 + l)
            cout << "P" << id;
        else if ((r - l) == 1)
            cout << "P" << id;
        else
            cout << " -";
    }
}

int main() {
    int num, quantum;
    cout << "Enter number of processes\n";
    cin >> num;
    vector<process> processes(num);
    cout << "Enter quantum\n";
    cin >> quantum;

    cout << "Enter burst time and priority for each process\n";
    for (int i = 0; i < num; i++) {
        cin >> processes[i].burst_time;
        processes[i].burst = processes[i].burst_time;
        processes[i].arrival = 0;
        processes[i].start = 0;
        processes[i].end = 0;
        processes[i].index = i + 1;
        processes[i].wait = 0;
        processes[i].turn = 0;
        processes[i].processed = 0;
    }

    queue<int> ready_queue;
    for (int i = 0; i < num; i++) {
        ready_queue.push(i);
    }

    int time = 0, l, r;
    while (!ready_queue.empty()) {
        int idx = ready_queue.front();
        ready_queue.pop();

        if (processes[idx].burst_time > quantum) {
            if (processes[idx].start == 0)
            {
                processes[idx].start = time;
            }
            
            l = time;
            time += quantum;
            r = time;
           
            gantt(processes, l, r, idx + 1);

            processes[idx].end = time;
            processes[idx].burst_time -= quantum;
            processes[idx].processed += quantum;
            ready_queue.push(idx);
        } else {
            if (processes[idx].start == 0)
                processes[idx].start = time;
            l = time;
            time += processes[idx].burst_time;
            r = time;
            gantt(processes, l, r, idx + 1);
            processes[idx].end = time;
            processes[idx].turn = processes[idx].end;
            //processes[idx].wait = processes[idx].start;
        }
    }

    cout << "\nProcess   Start   End\n";
    for (auto x : processes)
        cout << "P" << x.index << "\t" << x.start << "\t" << x.end << endl;

    
    for(int i=0; i<num; i++)
    {
        processes[i].wait = processes[i].turn - processes[i].burst;
    }
    int total_turnaround = 0, total_waiting = 0;
    for (auto x : processes) {
        total_turnaround += (x.turn - x.arrival);
        total_waiting += x.wait; 
    }
    double avg_turnaround = (double)total_turnaround / num;
    double avg_waiting = (double)total_waiting / num;

    cout << "Average Turnaround Time: " << avg_turnaround << endl;
    cout << "Average Waiting Time: " << avg_waiting << endl;

    return 0;
}