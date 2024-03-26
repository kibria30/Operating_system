#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int remainingTime;
    int arrivalTime;
    int turnaroundTime;
    int waitingTime;
};

void roundRobinScheduling(Process processes[], int n, int timeQuantum, vector<int>& ganttChart, vector<int>& ganttTime) {
    queue<Process*> readyQueue;
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                readyQueue.push(&processes[i]);
            }
        }

        if (!readyQueue.empty()) {
            Process* currentProcess = readyQueue.front();
            readyQueue.pop();

            int executionTime = min(timeQuantum, currentProcess->remainingTime);
            currentProcess->remainingTime -= executionTime;
            currentTime += executionTime;

            // Update Gantt Chart
            ganttChart.push_back(currentProcess->id);
            ganttTime.push_back(currentTime);

            if (currentProcess->remainingTime == 0) {
                ++completedProcesses;

                // Update turnaround time and waiting time
                currentProcess->turnaroundTime = currentTime - currentProcess->arrivalTime;
                currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
            }

        } else {
            ganttChart.push_back(0); // 0 represents idle time in Gantt chart
            ganttTime.push_back(currentTime);
            ++currentTime; // Idle time if no process is ready
        }
    }
}

int main() {
    int n;
    freopen("2_input.txt", "r", stdin);
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];

    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for Process " << processes[i].id << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for Process " << processes[i].id << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    int timeQuantum;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    vector<int> ganttChart, ganttTime;
    roundRobinScheduling(processes, n, timeQuantum, ganttChart, ganttTime);

    // Display Gantt Chart in the specified format
    cout << "\nGantt Chart:\n";
    for (int id : ganttChart) {
        if (id == 0) {
            cout << "|---" << "||";
        } else {
            cout << "---P" << id << "---||";
        }
    }
    cout << "\n";
    for (int time : ganttTime) {
        cout << time << "       ";
    }
    cout << "\n";

    // Display Table with Process ID, Turnaround Time, and Waiting Time
    cout << "\nProcess Table:\n";
    cout << "PID\tTurnaround Time\tWaiting Time\n";
    for (int i = 0; i < n; ++i) {
        cout << processes[i].id << "\t" << processes[i].turnaroundTime << "\t\t" << processes[i].waitingTime << "\n";
    }

    return 0;
}
