#include "./FCFS.h"
#include "./SJF.h"
#include "./RR.h"
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
using namespace std;

void completionTime(process *p)
{
    // calculating completion time
    p->completion_time = p->start_time + p->burst_time;
}

void waitingTime(process *process)
{
    // calculating waiting time
    process->waiting_time = process->turnaround_time - process->burst_time;
}

void turnAround(process *process)
{
    // calculating turn around time
    process->turnaround_time = process->completion_time - process->arrival_time;
}

void responseTime(process *process)
{
    // calculating response time
    process->response_time = process->start_time - process->arrival_time;
}

// args options
enum Sched_Alg
{
    FCFS,
    SJF,
    RR,
    ALL,
    INVALID
};

// retreiving args
Sched_Alg op_return(char *str)
{
    if (strcmp(str, "-fcfs") == 0)
        return FCFS;
    else if (strcmp(str, "-sjf") == 0)
        return SJF;
    else if (strcmp(str, "-rr") == 0)
        return RR;
    else if (strcmp(str, "-all") == 0)
        return ALL;
    return INVALID;
}

// file reading
void readFile(vector<process *> *processes)
{

    ofstream f;
    string line;
    // given file in canvas
    std::ifstream infile("processes.txt");

    if (infile.is_open())
    {
        // loop through the file and get every line
        while (getline(infile, line))
        {
            std::istringstream iss(line);
            int pid, burst_time, arrival_time;
            // pushing the numbers to the above vars
            // as the arrangment explaind in the assignment specs
            if (!(iss >> pid >> burst_time >> arrival_time))
            {
                break;
            }
            // allocate new process
            process *p = (process *)malloc(sizeof(process));
            p->pid = pid, p->burst_time = burst_time, p->arrival_time = arrival_time;

            // push process to the processes vector
            processes->push_back(p);
        }
    }
    f.close();
}

int main(int argc, char *argv[])
{

    vector<process *> processes;

    readFile(&processes);

    int time_quantum = 2;
    float context_switch = 0.1;

    // help menu
    string help_menu = "Choose one of the following algorithms as an argument:\n\t-all\t\tall algorithms\n\t-fcfs\t\tFirst-Come-First-Serve\n\t-sjf\t\tShortest-Job-First\n\t-rr\t\tRound-Robin";

    // check if argument are given then enter the switch statement
    if (argc > 1)
    {
        switch (op_return(argv[1]))
        {
        case FCFS:
            cout << "*********[FCFS]*********\n"
                 << endl;
            fcfs(&processes);
            break;
        case SJF:
            cout << "*********[SJF]*********\n"
                 << endl;
            sjf(&processes);
            break;
        case RR:
            cout << "*********[RR]*********\n"
                 << endl;
            rr(&processes, time_quantum, context_switch);
            break;
        case ALL:
            cout << "\n*********[FCFS]*********\n"
                 << endl;
            fcfs(&processes);
            cout << "\n*********[SJF]*********\n"
                 << endl;
            sjf(&processes);
            cout << "\n*********[RR]*********\n"
                 << endl;
            rr(&processes, time_quantum, context_switch);
            break;
        case INVALID:
            cout << help_menu << endl;
            break;
        default:
            break;
        }
    }
    else
    {
        cout << help_menu << endl;
    }

    // free allocated memory for processes
    for (unsigned int i = 0; i < processes.size(); i++)
        free(processes[i]);

    return 0;
}
