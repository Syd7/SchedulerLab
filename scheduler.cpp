#include <iostream>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <vector>

using namespace std;

struct Process{
    int index;
    int arrival;
    int burst;
    int remaining;
    int nice;
    int start_time = -1; //If you dont initialize it will be trash, and if it hasnt started it should be marked as something
    int completion_time = 0; //Will be set one completed, but before then it is 0 so it wont matter.
};

struct runningProcess{
     //we cannot put everything into process such as start, duration, etc as a process can appear multiple times
     // For example, if we work on pid 1 for 25ns and then go around and perform round robin, and we are back to pid 1, it will be hard to keep track of the 
     //history needed for the output.
    int start; // Time elapsed so far in ns
    int pid; // Process ID
    int duration; // CPU Time used in NS
    bool completed; //denotes if done (so we know if we need to print an X or not)
};

//intuition: put scheduling logic of each into its own method to allow for more modular writing and easier testing.
//vector<runningProcess> essentially talks about the timeline that we are expected to output.

//TODO: Implement all of these 
vector<runningProcess> fcfs(vector<Process> processes);
vector<runningProcess> rr(vector<Process> processes, int quantum);
vector<runningProcess> srtf(vector<Process> processes);
vector<runningProcess> p(vector<Process> processes);
vector<runningProcess> sjf(vector<Process> processes);



int main()
{
    int numTestCases;
    cin >> numTestCases;
    for (int i = 0; i < numTestCases; i++){
        int numProcesses;
        string schedulerType;
        cin >> numProcesses >> schedulerType;
        
        int timeQuantum;
        timeQuantum = 0;
        if (schedulerType == "RR"){
            cin >> timeQuantum;
        }
        vector<Process> processes(numProcesses); //We are using a vector because we are dynamically allocating memory.
        //for each process we need to iterate again right to eat it 
        for (int j = 0; j < numProcesses; j++){
            processes[j].index = j+1;
            cin >> processes[j].arrival >> processes[j].burst >> processes[j].nice;
            processes[j].remaining = processes[j].burst;
        }

        vector<runningProcess> timeline;

        if (schedulerType == "FCFS") {
            timeline = fcfs(processes);
        }
        else if (schedulerType == "RR") {
            timeline = rr(processes, timeQuantum);
        }
        else if (schedulerType == "SRTF") {
            timeline = srtf(processes);
        }
        else if (schedulerType == "P") {
            timeline = p(processes);
        }
        else if (schedulerType == "SJF"){
            timeline = sjf(processes);
        }

        // TODO: print output here
    }
    return 0;
}