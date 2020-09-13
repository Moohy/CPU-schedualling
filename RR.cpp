#include "RR.h"

bool compare1(process *p1, process *p2)
{
    return p1->arrival_time < p2->arrival_time;
}

bool compare2(process p1, process p2)
{
    return p1.pid < p2.pid;
}

void startTimeCalculation(process *p, float current_time)
{
    p->start_time = max(p->arrival_time, current_time);
}

void completionTime(process *p, float current_time)
{
    p->completion_time = current_time;
}

void rr(vector<process *> *processes, int time_quantum, float context_switch)
{
    // index to trace processes
    unsigned int index;

    // tracing rarmaining burst time for a process
    vector<float> remaining_burst(processes->size(), 0);

    // filling the arrray with full burst time corresponding to processes in processes vector
    for (unsigned int i = 0; i < processes->size(); i++)
        remaining_burst[i] = processes->at(i)->burst_time;

    // init queue
    queue<int> q;
    // push first start time
    q.push(0);

    // this is to be used for indecating the current time/start time for a process when it moves from ready to running
    float current_time = 0;

    // this is for checking the completness of processes
    vector<bool> is_completed(processes->size(), false);
    is_completed[0] = true;

    // counting the cpu time for processes that is processed plus the overhead time (context switch)
    float timer = 0;

    while (!q.empty())
    {
        // poping front of queue and use it as index
        index = q.front();
        q.pop();

        // calculate start time if current process is the queue front
        if (remaining_burst[index] == processes->at(index)->burst_time)
        {
            startTimeCalculation(processes->at(index), current_time);
            current_time = processes->at(index)->start_time;
        }

        // doing the process if still isn't reached 0 burst time
        if (remaining_burst[index] - time_quantum > 0)
        {
            // substracting quantum time from burst time
            remaining_burst[index] -= time_quantum;

            // add quontum time and context switch over load to timer
            timer += time_quantum + context_switch;
            current_time += time_quantum;
        }
        else
        {
            // add remaining cpu burst time + overhead time
            timer += remaining_burst[index] + context_switch;

            current_time += remaining_burst[index];
            remaining_burst[index] = 0;

            // do calculation for process
            completionTime(processes->at(index), current_time);
            turnAround(processes->at(index));
            waitingTime(processes->at(index));
            responseTime(processes->at(index));
        }

        for (unsigned int i = 1; i < processes->size(); i++)
        {
            // check completness
            if (remaining_burst[i] > 0 && processes->at(i)->arrival_time <= current_time && is_completed[i] == false)
            {
                q.push(i);
                is_completed[i] = true;
            }
        }

        // if not finished
        if (remaining_burst[index] > 0)
            q.push(index);

        // if queue is empty but there is an unfinished process
        if (q.empty())
        {
            for (unsigned int i = 1; i < processes->size(); i++)
            {
                if (remaining_burst[i] > 0)
                {
                    q.push(i);
                    is_completed[i] = true;
                    break;
                }
            }
        }
    }

    /*
        printing all neccessery information
    */
    cout << "PID "
         << " Waiting time "
         << " Turn around time"
         << endl;

    for (unsigned int i = 0; i < processes->size(); i++)
        cout << " " << processes->at(i)->pid << "\t" << processes->at(i)->waiting_time << "\t\t" << processes->at(i)->turnaround_time << endl;

    cout << "\nCPU clock time = "
         << timer << endl;
}