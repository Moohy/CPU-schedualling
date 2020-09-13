# CPU Scheduling Program
### To compile the program
```bash
make
```
- make sure that the processes file is placed in Sched directory and called `processes.txt`
- the arrangement of processes.txt file is <pid, burst time, arrival time> 

### To change the processes file name
- Open `app.cpp` 
- Navigate to `readFile(vector<process *> *processes)` function
- Change "processes.txt" in `std::ifstream infile("processes.txt");` to the file name

### To change time quantum and context switch values
- Open `app.cpp` 
- Navigate to `main()`
- Change time quantum and context switch variables

## Run All algorithms
- pass -all argument as the box below show
    ```bash
    ./app -all
    ```

## Run FCFS algorithm
- pass -fcfs argument as the box below show
    ```bash
    ./app -fcfs
    ```

## Run SJF algorithm
- pass -SJF argument as the box below show
    ```bash
    ./app -sjf
    ```

## Run RR algorithm
- pass -rr argument as the box below show
    ```bash
    ./app -rr
    ```