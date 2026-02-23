#include <iostream>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <climits>

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
     // history needed for the output.
    int start; // Time elapsed so far in ns
    int pid; // Process ID
    int duration; // CPU Time used in NS
    bool completed; //denotes if done (so we know if we need to print an X or not)
};

//intuition: put scheduling logic of each into its own method to allow for more modular writing and easier testing.
//vector<runningProcess> essentially talks about the timeline that we are expected to output.

bool AllProcessesDoneStatus(vector<Process>& p) {
    for (int i = 0; i < p.size(); i++){
        if (p[i].remaining > 0) {
            return false;
        }
    }
    return true;
}
vector<runningProcess> fcfs(vector<Process> &processes){

    vector<runningProcess> timeline;
    int totalTime = 0;
    //sort accordingly (arrival Time First -> if equal arrival time, then sort by index)
    sort(processes.begin(), processes.end(), [](Process &a, Process &b) { //note we use a reference so we dont recopy each process.
        if (a.arrival == b.arrival) {
            return a.index < b.index;  // tie-breaker: smaller index comes first
        } else {
            return a.arrival < b.arrival;  // earlier arrival comes first
        }
    });

    for (int i = 0; i < processes.size(); i++){
        int pid = processes[i].index;
        int arrival = processes[i].arrival;
        int burst = processes[i].burst;
        if (totalTime < arrival){
            totalTime = arrival;
        }
        runningProcess rp;

        rp.start = totalTime;
        rp.pid = pid;
        rp.duration = burst;
        rp.completed = true;

        processes[i].start_time = totalTime;
        totalTime = totalTime + rp.duration;
        //also edit the processor stuff mismo so we can use it for calculation later
        processes[i].completion_time = totalTime;
        processes[i].remaining = 0;

        timeline.push_back(rp);

    }
    return timeline;
}

vector<runningProcess> srtf(vector<Process> &processes) {
    vector<runningProcess> timeline;
    int currentTime = 0;
    while (!AllProcessesDoneStatus(processes)) {
        int shortestProcessIndex = -1;
        int shortestProcessTime = INT_MAX;

        for (int i = 0; i < processes.size(); i++) {
            // Only consider processes that have arrived and are not finished
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                if (processes[i].remaining < shortestProcessTime) {
                    // New shortest found
                    shortestProcessTime = processes[i].remaining;
                    shortestProcessIndex = i;
                }
                else if (processes[i].remaining == shortestProcessTime) {
                    // If there is a tie, choose the earlier arrival
                    if (processes[i].arrival < processes[shortestProcessIndex].arrival) {
                        shortestProcessIndex = i;
                    }
                    // If arrival is also the same, choose lower index
                    else if (processes[i].arrival == processes[shortestProcessIndex].arrival && processes[i].index < processes[shortestProcessIndex].index) {
                        shortestProcessIndex = i;
                    }
                }
            }
}

        // If no processes can be used, increment current time. No need to repeat the rest of the code below
        if (shortestProcessIndex == -1) {
            currentTime += 1;
            continue;
        }

        // Determine next arrival that might preempt
        int runTime = processes[shortestProcessIndex].remaining; //check remaining
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].remaining > 0 && processes[i].arrival > currentTime) {
                int timeUntilArrival = processes[i].arrival - currentTime; //how much time until next process arrives
                int remainingAtArrival = processes[shortestProcessIndex].remaining - timeUntilArrival;
                if (timeUntilArrival < runTime && processes[i].remaining < remainingAtArrival) {
                    runTime = timeUntilArrival; // essentially, we just want to limit the amount of time the process will run so we dont accidentally run it for too long
                    // if a next process is coming, then we have to preempt accordingly
                }
            }
        }

        // Set start_time if first time running
        if (processes[shortestProcessIndex].start_time == -1)
            processes[shortestProcessIndex].start_time = currentTime;

        
        //populate timeline with rp
        runningProcess rp;
        rp.start = currentTime;
        rp.pid = processes[shortestProcessIndex].index;
        rp.duration = runTime;

        processes[shortestProcessIndex].remaining -= runTime; // subtract remaining by the amount of time process was run for
        currentTime += runTime; // move time forward.

        if (processes[shortestProcessIndex].remaining == 0) { //check for completion
            processes[shortestProcessIndex].completion_time = currentTime; //set completion time to current time
            rp.completed = true; // mark completed
        } else {
            rp.completed = false;
        }

        timeline.push_back(rp); // push rp to timeine
    }

    return timeline;
}
vector<runningProcess> rr(vector<Process> &processes, int quantum) {
    vector<runningProcess> timeline;
    int n = processes.size();
    int completed = 0;
    int currentTime = 0;
    int nextArrivalIndex = 0; // index for new arrivals

    // Sort processes by arrival time, then index
    sort(processes.begin(), processes.end(), [](Process &a, Process &b) { //note we use a reference so we dont recopy each process.
        if (a.arrival == b.arrival) {
            return a.index < b.index;  // tie-breaker: smaller index comes first
        } else {
            return a.arrival < b.arrival;  // earlier arrival comes first
        }
    });


    queue<int> fresh; // newly arrived processes
    queue<int> used;  // preempted processes

    //while the number of completed processes is less than the total processes
    while(!AllProcessesDoneStatus(processes)) {
        // Push newly arrived processes into fresh queue
        while(nextArrivalIndex < n && processes[nextArrivalIndex].arrival <= currentTime) {     // while the current index is less than the total proccesses, and the arrival time is on or before the current time
            fresh.push(nextArrivalIndex); //push the index of that process onto the fresh queue
            nextArrivalIndex++;     // increment
        }

        //  idle handling for cpu
        if(fresh.empty() && used.empty()) {
            currentTime = processes[nextArrivalIndex].arrival; //skips to the next processes arrival time instead of incrementing every time the queue is empty
            continue;
        }

        // pick the next process to be run, fresh processes first. This follows the specs where new arrivals are given priority
        int processIndex;
        if(!fresh.empty()) { //if there are fresh processes, we take the first fresh process and execute that
            processIndex = fresh.front(); 
            fresh.pop();
        } else {
            processIndex = used.front();  //otherwise we take from the queue of old processes or processes that did not finish in one slice
            used.pop();
        }

        Process &p = processes[processIndex];

        // Set start time if first run
        if(p.start_time == -1){
            p.start_time = currentTime;
        } 

        //check how much time is needed. if the remaining time is less than the quantum
        //(aka the process finishes before the whole slice is used), the runtime for that process iteration is just the remaining time
        int runTime = min(quantum, p.remaining);
        p.remaining -= runTime; //adjusts the remaining time of the process

        runningProcess rp;
        rp.start = currentTime;
        rp.pid = p.index;
        rp.duration = runTime;
        rp.completed = false;
        currentTime += runTime;
        bool finished = false;

        //if the remaining time is finished, set finished to true, which is uused in the next block
        if (p.remaining == 0){
            finished = true;
        }
      
        //if the process is finished, we mark the process as complete and edit its variables
        if(finished) {
            rp.completed = true;
            p.completion_time = currentTime;
        }

        timeline.push_back(rp);

        // Push any newly arrived processes during this slice to fresh
        //this works because it wwe've previously iterated any older processes and the current time has since increased!
        while(nextArrivalIndex < n && processes[nextArrivalIndex].arrival <= currentTime) {
            fresh.push(nextArrivalIndex);
            nextArrivalIndex++;
        }

        // If not finished, put process at the back of used queue, its now used </3 and not fresj
        if(!finished) {
            used.push(processIndex);
        }
    }
    return timeline;
}
        
vector<runningProcess> p(vector<Process> &processes){
    vector<runningProcess> timeline;
    int currentTime = 0;
    while (!AllProcessesDoneStatus(processes)) {
        int mostPriorityIndex = -1;
        int mostPriorityNiceness = 21;
        for (int i = 0; i < processes.size(); i ++){
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                if (processes[i].nice < mostPriorityNiceness){
                    //new most priority 
                    mostPriorityNiceness = processes[i].nice;
                    mostPriorityIndex = i;
                }
                else if (processes[i].nice == mostPriorityNiceness){
                    //choose the earlier arrival time.
                    if (processes[i].arrival < processes[mostPriorityIndex].arrival){
                        mostPriorityIndex = i;;
                    }
                    else if (processes[i].arrival == processes[mostPriorityIndex].arrival && processes[i].index < processes[mostPriorityIndex].index){
                        mostPriorityIndex = i;
                    } 
                }
            }
        }
        if (mostPriorityIndex == -1) {
            currentTime += 1; // if we dont find a viable index then just increment current time.
            continue;
        }
        int runTime = processes[mostPriorityIndex].remaining;
        for (int i = 0; i < processes.size(); i++){
            if (processes[i].remaining > 0 && processes[i].arrival > currentTime){
                int timeUntilArrival = processes[i].arrival - currentTime;
                if (timeUntilArrival < runTime && processes[i].nice < processes[mostPriorityIndex].nice){
                    runTime = timeUntilArrival;
                }
            }
        }
        if (processes[mostPriorityIndex].start_time == -1)
            processes[mostPriorityIndex].start_time = currentTime;
        runningProcess rp;
        rp.start = currentTime;
        rp.pid = processes[mostPriorityIndex].index;
        rp.duration = runTime;

        processes[mostPriorityIndex].remaining -= runTime; // subtract remaining by the amount of time process was run for
        currentTime += runTime; // move time forward.

        if (processes[mostPriorityIndex].remaining == 0) { //check for completion
            processes[mostPriorityIndex].completion_time = currentTime; //set completion time to current time
            rp.completed = true; // mark completed
        } else {
            rp.completed = false;
        }

        timeline.push_back(rp); // push rp to timeine
    }

    return timeline;

}
vector<runningProcess> sjf(vector<Process> &processes){
    
    vector<runningProcess> timeline;
    int currentTime = 0;

    //sort accordingly (arrival Time First -> if equal arrival time, then sort by index)
    //we have to sort by arrival time first incase of bursts of same length *insert choking emoji*
    sort(processes.begin(), processes.end(), [](Process &a, Process &b) { //note we use a reference so we dont recopy each process.
        if (a.arrival == b.arrival) {
            return a.index < b.index;  // tie-breaker: smaller index comes first
        } else {
            return a.arrival < b.arrival;  // earlier arrival comes first
        }
    });

    while (!AllProcessesDoneStatus(processes)){

        int shortestJobIndex = -1;
        int shortestBurst = INT_MAX;

        //find the shortest process
        //comparing current burst to the current shortest burst
        for (int i = 0; i < processes.size(); i++){
            if (processes[i].remaining > 0 && processes[i].arrival <= currentTime){
                if(processes[i].burst < shortestBurst){
                shortestBurst = processes[i].burst;
                shortestJobIndex = i;
            }
            }
        }

        //non-preemptive idle time handling, if the processes still come after the current time
        if (shortestJobIndex == -1){
            int nextArrivalTime = INT_MAX;
            for (int i = 0; i < (int)processes.size(); i++) {
                // remaining time > 0 || the current processes arrival time is currently  earlier than the other processes arrival time
                if (processes[i].remaining > 0 && processes[i].arrival < nextArrivalTime) {
                    nextArrivalTime = processes[i].arrival;
                }
        }
        currentTime = nextArrivalTime;
        //rerun the program from the beginning
        continue;

    }
        runningProcess rp;
        rp.start = currentTime;
        rp.pid = processes[shortestJobIndex].index;
        rp.duration = processes[shortestJobIndex].burst;
        rp.completed = true;
        processes[shortestJobIndex].start_time = currentTime;
        currentTime += rp.duration;
        //also edit the processor stuff mismo so we can use it for calculation later
        processes[shortestJobIndex].completion_time = currentTime;
        processes[shortestJobIndex].remaining = 0;
        timeline.push_back(rp);

    }
    return timeline;

}

void parseTimeline(vector<runningProcess> &timeline, vector<Process> &processes, string schedulerType, int testIndex) {
    cout << testIndex + 1 << " " << schedulerType << "\n";

    for (int i = 0; i < timeline.size(); i++){                                                          //visit every execution slice stored in the timeline vector
        if (timeline[i].completed){                                                                     //check if the burst was the final one for the that process
            cout << timeline[i].start << " " <<timeline[i].pid << " " <<timeline[i].duration <<"X";     //start time, process id, duration
        }
        else{
            cout << timeline[i].start << " " <<timeline[i].pid << " " <<timeline[i].duration;           //same, but if process has not been completed
        }
        cout << "\n";
    }
    int n = processes.size();               //get number of unique processes in the timeline 
    vector<int> waitingTime(n + 1, 0);      //vector = dynamic array, dynamic array of waiting time per processes. n+1 so we can use the index to access the waiting time
    vector<int> turnaroundTime(n + 1, 0);   //same explanation but turnaround
    vector<int> responseTime(n + 1, -1);    //same explanation but responsetime

    int totalCPUBurst = 0;
    int totalTimeElapsed = 0;
    int totalProcessesCompleted = 0;
    
    //Motivation: Total Time Elapsed can be calculated by getting the start of the last process ran + the duration it was ran for.
    totalTimeElapsed = timeline.back().start + timeline.back().duration;

    cout << "Total Time Elapsed: " << totalTimeElapsed << "ns \n";
    //total CPU burst calculation and other calculation stuff needed
    for (int i = 0; i < timeline.size(); i++){
        totalCPUBurst += timeline[i].duration;
        if (timeline[i].completed){
            totalProcessesCompleted += 1;
        }

    }
    cout << "Total CPU Burst Time: " << totalCPUBurst << "ns \n";
    float cpuUtil = 0;
    cpuUtil = (float) totalCPUBurst / (float)totalTimeElapsed * 100; //need to cast to float or else we will integer divide the two, ultimately ending up with a zero.
    cout <<"CPU Utilization: " << (int) cpuUtil <<"% \n";
    float throughput = 0;
    throughput = (float) totalProcessesCompleted / (float) totalTimeElapsed;
    cout << "Throughput: " << throughput << " processes/ns" << "\n";

    //resort the processes by index. allows the correct math to be done regardless of sched algorithm 
    sort(processes.begin(), processes.end(), [](Process &a, Process &b) {
        return a.index < b.index;
    });

        //the equations for these is from the slides. TT = CT - AT; RT = ST - AT
      for (int i = 0; i < timeline.size(); i++){
        int pid = timeline[i].pid;
        int processStartTime = timeline[i].start;
        int processArrivalTime = processes[pid-1].arrival;
        int processCompletetionTime = processes[pid-1].completion_time;

        //Response Time
        if (responseTime[pid] == -1){
            responseTime[pid] = processStartTime - processArrivalTime;
        }

        //Turnaround Time
        if (timeline[i].completed == true){
            turnaroundTime[pid] = processCompletetionTime - processArrivalTime;
        }    
    }

    //Waitingn time 
    cout << "Waiting times:\n";
    float sumWaitingTimes = 0;                                              //will be used for calculation of average waiting time
    
    for (int j = 0; j < n; j++){                                            //for every j less than the amount of processes
        int pid = processes[j].index;
        waitingTime[pid] = turnaroundTime[pid] - processes[j].burst;  
        sumWaitingTimes += waitingTime[pid];
        cout << " Process " << pid << ": " << waitingTime[pid] << "ns" << "\n";
    }

    float averageWaitingTimes = sumWaitingTimes/n;
    cout << "Average waiting time: " << averageWaitingTimes << "ns" << "\n";

    cout <<"Turnaround times:\n";
    float sumTurnaroundTime = 0;                                              //will be used for calculation of average waiting time

    for (int j = 0; j < n; j++){
        int pid = processes[j].index;
        cout << " Process " << pid << ": " <<turnaroundTime[pid] <<"ns" <<"\n";
        sumTurnaroundTime += turnaroundTime[pid];
    }
    float averageTurnaroundTime = sumTurnaroundTime / n;
    cout << "Average turnaround time: " << averageTurnaroundTime <<"ns" <<"\n";

    cout <<"Response times:\n";
    float totalResponseTime = 0;

    for (int j = 0; j < n; j++){
        int pid = processes[j].index;
        cout << " Process " << pid << ": " <<responseTime[pid] <<"ns" <<"\n";
        totalResponseTime += responseTime[pid];
    }
    float averageResponseTime = totalResponseTime / n;
    cout << "Average response time: " << averageResponseTime <<"ns" <<"\n";

}

int main()
{
    int numTestCases;
    cin >> numTestCases;
    vector<vector<runningProcess>> allTimelines; // each element is a timeline for one test case
    vector<vector<Process>> allProcesses;
    vector<string> schedulerTypeTimeline;
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
            processes[j].index = j+1;                   //very important so pid always starts at 1
            cin >> processes[j].arrival >> processes[j].burst >> processes[j].nice;
            processes[j].remaining = processes[j].burst;
        }

        vector<runningProcess> timeline;
        if (schedulerType == "FCFS") {
            timeline = fcfs(processes);
        }
        //TODO: Uncomment out each line when done for testing!
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

        // Compute metrics
        allTimelines.push_back(timeline);
        allProcesses.push_back(processes);
        schedulerTypeTimeline.push_back(schedulerType);
    }
    for (int i = 0; i < allTimelines.size(); i++){
        parseTimeline(allTimelines[i], allProcesses[i], schedulerTypeTimeline[i], i);
    }
    return 0;
}