def compare_outputs(text1, text2):
    lines1 = text1.strip().splitlines()
    lines2 = text2.strip().splitlines()

    max_len = max(len(lines1), len(lines2))

    for i in range(max_len):
        l1 = lines1[i].strip() if i < len(lines1) else "<NO LINE>"
        l2 = lines2[i].strip() if i < len(lines2) else "<NO LINE>"

        # case-insensitive comparison
        if l1.lower() != l2.lower():
            print(f"Difference at line {i+1}:")
            print("  Output 1:", l1)
            print("  Output 2:", l2)
            print()

# Paste your first block inside triple quotes
text1 = """1 FCFS
0 2 50X
50 1 50X
100 4 50X
150 3 50X
Total Time Elapsed: 200ns
Total CPU Burst Time: 200ns
CPU Utilization: 100%
Throughput: 0.02 processes/ns
Waiting times:
 Process 1: 10ns
 Process 2: 0ns
 Process 3: 30ns
 Process 4: 20ns
Average waiting time: 15ns
Turnaround times:
 Process 1: 60ns
 Process 2: 50ns
 Process 3: 80ns
 Process 4: 70ns
Average turnaround time: 65ns
Response times:
 Process 1: 10ns
 Process 2: 0ns
 Process 3: 30ns
 Process 4: 20ns
Average response time: 15ns
2 FCFS
100 3 30X
200 2 30X
300 1 30X
Total Time Elapsed: 330ns
Total CPU Burst Time: 90ns
CPU Utilization: 27.2727%
Throughput: 0.00909091 processes/ns
Waiting times:
 Process 1: 0ns
 Process 2: 0ns
 Process 3: 0ns
Average waiting time: 0ns
Turnaround times:
 Process 1: 30ns
 Process 2: 30ns
 Process 3: 30ns
Average turnaround time: 30ns
Response times:
 Process 1: 0ns
 Process 2: 0ns
 Process 3: 0ns
Average response time: 0ns
3 SJF
0 2 20X
20 3 30X
50 4 30X
80 1 40X
Total Time Elapsed: 120ns
Total CPU Burst Time: 120ns
CPU Utilization: 100%
Throughput: 0.0333333 processes/ns
Waiting times:
 Process 1: 80ns
 Process 2: 0ns
 Process 3: 20ns
 Process 4: 50ns
Average waiting time: 37.5ns
Turnaround times:
 Process 1: 120ns
 Process 2: 20ns
 Process 3: 50ns
 Process 4: 80ns
Average turnaround time: 67.5ns
Response times:
 Process 1: 80ns
 Process 2: 0ns
 Process 3: 20ns
 Process 4: 50ns
Average response time: 37.5ns
4 SJF
20 1 50X
70 2 10X
80 3 10X
Total Time Elapsed: 90ns
Total CPU Burst Time: 70ns
CPU Utilization: 77.7778%
Throughput: 0.0333333 processes/ns
Waiting times:
 Process 1: 0ns
 Process 2: 40ns
 Process 3: 30ns
Average waiting time: 23.3333ns
Turnaround times:
 Process 1: 50ns
 Process 2: 50ns
 Process 3: 40ns
Average turnaround time: 46.6667ns
Response times:
 Process 1: 0ns
 Process 2: 40ns
 Process 3: 30ns
Average response time: 23.3333ns
5 SRTF
0 2 20X
20 3 30X
50 4 30X
80 1 40X
Total Time Elapsed: 120ns
Total CPU Burst Time: 120ns
CPU Utilization: 100%
Throughput: 0.0333333 processes/ns
Waiting times:
 Process 1: 80ns
 Process 2: 0ns
 Process 3: 20ns
 Process 4: 50ns
Average waiting time: 37.5ns
Turnaround times:
 Process 1: 120ns
 Process 2: 20ns
 Process 3: 50ns
 Process 4: 80ns
Average turnaround time: 67.5ns
Response times:
 Process 1: 80ns
 Process 2: 0ns
 Process 3: 20ns
 Process 4: 50ns
Average response time: 37.5ns
6 SRTF
20 1 10
30 2 10X
40 1 10
50 3 10X
60 1 30X
Total Time Elapsed: 90ns
Total CPU Burst Time: 70ns
CPU Utilization: 77.7778%
Throughput: 0.0333333 processes/ns
Waiting times:
 Process 1: 20ns
 Process 2: 0ns
 Process 3: 0ns
Average waiting time: 6.66667ns
Turnaround times:
 Process 1: 70ns
 Process 2: 10ns
 Process 3: 10ns
Average turnaround time: 30ns
Response times:
 Process 1: 0ns
 Process 2: 0ns
 Process 3: 0ns
Average response time: 0ns
7 P
0 2 50X
50 1 30
80 4 40
120 3 50X
170 4 10X
180 1 20X
Total Time Elapsed: 200ns
Total CPU Burst Time: 200ns
CPU Utilization: 100%
Throughput: 0.02 processes/ns
Waiting times:
 Process 1: 110ns
 Process 2: 0ns
 Process 3: 0ns
 Process 4: 50ns
Average waiting time: 40ns
Turnaround times:
 Process 1: 160ns
 Process 2: 50ns
 Process 3: 50ns
 Process 4: 100ns
Average turnaround time: 90ns
Response times:
 Process 1: 10ns
 Process 2: 0ns
 Process 3: 0ns
 Process 4: 0ns
Average response time: 2.5ns
8 P
0 2 20X
20 1 20X
40 3 10
50 4 10
60 6 20X
80 5 20X
100 4 10X
110 3 10X
Total Time Elapsed: 120ns
Total CPU Burst Time: 120ns
CPU Utilization: 100%
Throughput: 0.05 processes/ns
Waiting times:
 Process 1: 20ns
 Process 2: 0ns
 Process 3: 100ns
 Process 4: 40ns
 Process 5: 10ns
 Process 6: 0ns
Average waiting time: 28.3333ns
Turnaround times:
 Process 1: 40ns
 Process 2: 20ns
 Process 3: 120ns
 Process 4: 60ns
 Process 5: 30ns
 Process 6: 20ns
Average turnaround time: 48.3333ns
Response times:
 Process 1: 20ns
 Process 2: 0ns
 Process 3: 40ns
 Process 4: 0ns
 Process 5: 10ns
 Process 6: 0ns
Average response time: 11.6667ns
9 RR
0 2 10
10 2 10
20 2 10
30 2 10
40 1 10
50 2 10X
60 1 10
70 1 10
80 4 10
90 1 10
100 4 10
110 1 10X
120 4 10
130 3 10
140 4 10
150 3 10
160 4 10X
170 3 10
180 3 10
190 3 10X
Total Time Elapsed: 200ns
Total CPU Burst Time: 200ns
CPU Utilization: 100%
Throughput: 0.02 processes/ns
Waiting times:
 Process 1: 30ns
 Process 2: 10ns
 Process 3: 30ns
 Process 4: 40ns
Average waiting time: 27.5ns
Turnaround times:
 Process 1: 80ns
 Process 2: 60ns
 Process 3: 80ns
 Process 4: 90ns
Average turnaround time: 77.5ns
Response times:
 Process 1: 0ns
 Process 2: 0ns
 Process 3: 10ns
 Process 4: 0ns
Average response time: 2.5ns
10 RR
0 3 25
25 2 15X
40 3 25
65 1 25
90 4 25
115 5 25
140 3 25
165 1 10X
175 4 25
200 5 25
225 3 25X
250 4 25
275 5 20X
295 4 5X
Total Time Elapsed: 300ns
Total CPU Burst Time: 300ns
CPU Utilization: 100%
Throughput: 0.0166667 processes/ns
Waiting times:
 Process 1: 110ns
 Process 2: 15ns
 Process 3: 150ns
 Process 4: 190ns
 Process 5: 174ns
Average waiting time: 127.8ns
Turnaround times:
 Process 1: 145ns
 Process 2: 30ns
 Process 3: 250ns
 Process 4: 270ns
 Process 5: 244ns
Average turnaround time: 187.8ns
Response times:
 Process 1: 35ns
 Process 2: 15ns
 Process 3: 0ns
 Process 4: 60ns
 Process 5: 64ns
Average response time: 34.8ns"""

text2 = """1 FCFS
0 2 50X
50 1 50X
100 4 50X
150 3 50X
Total time elapsed: 200ns
Total CPU burst time: 200ns
CPU Utilization: 100%
Throughput: 0.02 processes/ns
Waiting times:
 Process 1: 10ns
 Process 2: 0ns
 Process 3: 30ns
 Process 4: 20ns
Average waiting time: 15ns
Turnaround times:
 Process 1: 60ns
 Process 2: 50ns
 Process 3: 80ns
 Process 4: 70ns
Average turnaround time: 65ns
Response times:
 Process 1: 10ns
 Process 2: 0ns
 Process 3: 30ns
 Process 4: 20ns
Average response time: 15ns
2 FCFS
100 3 30X
200 2 30X
300 1 30X
Total time elapsed: 330ns
Total CPU burst time: 90ns
CPU Utilization: 27%
Throughput: 0.00909091 processes/ns
Waiting times:
 Process 1: 0ns
 Process 2: 0ns
 Process 3: 0ns
Average waiting time: 0ns
Turnaround times:
 Process 1: 30ns
 Process 2: 30ns
 Process 3: 30ns
Average turnaround time: 30ns
Response times:
 Process 1: 0ns
 Process 2: 0ns
 Process 3: 0ns
Average response time: 0ns
3 SJF
0 2 20X
20 3 30X
50 4 30X
80 1 40X
Total time elapsed: 120ns
Total CPU burst time: 120ns
CPU Utilization: 100%
Throughput: 0.0333333 processes/ns
Waiting times:
 Process 1: 80ns
 Process 2: 0ns
 Process 3: 20ns
 Process 4: 50ns
Average waiting time: 37.5ns
Turnaround times:
 Process 1: 120ns
 Process 2: 20ns
 Process 3: 50ns
 Process 4: 80ns
Average turnaround time: 67.5ns
Response times:
 Process 1: 80ns
 Process 2: 0ns
 Process 3: 20ns
 Process 4: 50ns
Average response time: 37.5ns
4 SJF
20 1 50X
70 2 10X
80 3 10X
Total time elapsed: 90ns
Total CPU burst time: 70ns
CPU Utilization: 77%
Throughput: 0.0333333 processes/ns
Waiting times:
 Process 1: 0ns
 Process 2: 40ns
 Process 3: 30ns
Average waiting time: 23.3333ns
Turnaround times:
 Process 1: 50ns
 Process 2: 50ns
 Process 3: 40ns
Average turnaround time: 46.6667ns
Response times:
 Process 1: 0ns
 Process 2: 40ns
 Process 3: 30ns
Average response time: 23.3333ns
5 SRTF
0 2 20X
20 3 30X
50 4 30X
80 1 40X
Total time elapsed: 120ns
Total CPU burst time: 120ns
CPU Utilization: 100%
Throughput: 0.0333333 processes/ns
Waiting times:
 Process 1: 80ns
 Process 2: 0ns
 Process 3: 20ns
 Process 4: 50ns
Average waiting time: 37.5ns
Turnaround times:
 Process 1: 120ns
 Process 2: 20ns
 Process 3: 50ns
 Process 4: 80ns
Average turnaround time: 67.5ns
Response times:
 Process 1: 80ns
 Process 2: 0ns
 Process 3: 20ns
 Process 4: 50ns
Average response time: 37.5ns
6 SRTF
20 1 10
30 2 10X
40 1 10
50 3 10X
60 1 30X
Total time elapsed: 90ns
Total CPU burst time: 70ns
CPU Utilization: 77%
Throughput: 0.0333333 processes/ns
Waiting times:
 Process 1: 20ns
 Process 2: 0ns
 Process 3: 0ns
Average waiting time: 6.66667ns
Turnaround times:
 Process 1: 70ns
 Process 2: 10ns
 Process 3: 10ns
Average turnaround time: 30ns
Response times:
 Process 1: 0ns
 Process 2: 0ns
 Process 3: 0ns
Average response time: 0ns
7 P
0 2 50X
50 1 30
80 4 40
120 3 50X
170 4 10X
180 1 20X
Total time elapsed: 200ns
Total CPU burst time: 200ns
CPU Utilization: 100%
Throughput: 0.02 processes/ns
Waiting times:
 Process 1: 110ns
 Process 2: 0ns
 Process 3: 0ns
 Process 4: 50ns
Average waiting time: 40ns
Turnaround times:
 Process 1: 160ns
 Process 2: 50ns
 Process 3: 50ns
 Process 4: 100ns
Average turnaround time: 90ns
Response times:
 Process 1: 10ns
 Process 2: 0ns
 Process 3: 0ns
 Process 4: 0ns
Average response time: 2.5ns
8 P
0 2 20X
20 1 20X
40 3 10
50 4 10
60 6 20X
80 5 20X
100 4 10X
110 3 10X
Total time elapsed: 120ns
Total CPU burst time: 120ns
CPU Utilization: 100%
Throughput: 0.05 processes/ns
Waiting times:
 Process 1: 20ns
 Process 2: 0ns
 Process 3: 100ns
 Process 4: 40ns
 Process 5: 10ns
 Process 6: 0ns
Average waiting time: 28.3333ns
Turnaround times:
 Process 1: 40ns
 Process 2: 20ns
 Process 3: 120ns
 Process 4: 60ns
 Process 5: 30ns
 Process 6: 20ns
Average turnaround time: 48.3333ns
Response times:
 Process 1: 20ns
 Process 2: 0ns
 Process 3: 40ns
 Process 4: 0ns
 Process 5: 10ns
 Process 6: 0ns
Average response time: 11.6667ns
9 RR
0 2 10
10 2 10
20 2 10
30 2 10
40 1 10
50 2 10X
60 1 10
70 1 10
80 4 10
90 1 10
100 4 10
110 1 10X
120 4 10
130 3 10
140 4 10
150 3 10
160 4 10X
170 3 10
180 3 10
190 3 10X
Total time elapsed: 200ns
Total CPU burst time: 200ns
CPU Utilization: 100%
Throughput: 0.02 processes/ns
Waiting times:
 Process 1: 30ns
 Process 2: 10ns
 Process 3: 30ns
 Process 4: 40ns
Average waiting time: 27.5ns
Turnaround times:
 Process 1: 80ns
 Process 2: 60ns
 Process 3: 80ns
 Process 4: 90ns
Average turnaround time: 77.5ns
Response times:
 Process 1: 0ns
 Process 2: 0ns
 Process 3: 10ns
 Process 4: 0ns
Average response time: 2.5ns
10 RR
0 3 25
25 2 15X
40 3 25
65 1 25
90 4 25
115 5 25
140 3 25
165 1 10X
175 4 25
200 5 25
225 3 25X
250 4 25
275 5 20X
295 4 5X
Total time elapsed: 300ns
Total CPU burst time: 300ns
CPU Utilization: 100%
Throughput: 0.0166667 processes/ns
Waiting times:
 Process 1: 110ns
 Process 2: 15ns
 Process 3: 150ns
 Process 4: 190ns
 Process 5: 174ns
Average waiting time: 127.8ns
Turnaround times:
 Process 1: 145ns
 Process 2: 30ns
 Process 3: 250ns
 Process 4: 270ns
 Process 5: 244ns
Average turnaround time: 187.8ns
Response times:
 Process 1: 35ns
 Process 2: 15ns
 Process 3: 0ns
 Process 4: 60ns
 Process 5: 64ns
Average response time: 34.8ns
"""
compare_outputs(text1, text2)