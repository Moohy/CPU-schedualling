#include "rr.h"

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

    // float cs = 0.1;
    // sort(*processes, *(processes + processes->size()), compare1);

    unsigned int index;
    vector<float> remaining_brust(processes->size(), 0);

    for (unsigned int i = 0; i < processes->size(); i++)
        remaining_brust[i] = processes->at(i)->burst_time;

    // cout << setprecision(2) << fixed;

    queue<int> q;
    float current_time = 0;
    q.push(0);
    vector<bool> is_completed(processes->size(), false);
    is_completed[0] = true;
    float timer = 0;
    while (!q.empty())
    {
        // poping front of queue and use it as index
        index = q.front();
        q.pop();

        // calculate start time if current process is the queue front
        if (remaining_brust[index] == processes->at(index)->burst_time)
        {
            startTimeCalculation(processes->at(index), current_time);
            current_time = processes->at(index)->start_time;
        }

        // doing the process if still isn't reached 0 burst time
        if (remaining_brust[index] - time_quantum > 0)
        {
            // substracting quantum time from burst time
            remaining_brust[index] -= time_quantum;

            // add quontum time and context switch over load to timer
            timer += time_quantum + context_switch;
            current_time += time_quantum;
        }
        else
        {
            timer += remaining_brust[index] + context_switch;
            current_time += remaining_brust[index];
            remaining_brust[index] = 0;

            completionTime(processes->at(index), current_time);
            turnAround(processes->at(index));
            waitingTime(processes->at(index));
            responseTime(processes->at(index));
        }

        for (unsigned int i = 1; i < processes->size(); i++)
        {
            if (remaining_brust[i] > 0 && processes->at(i)->arrival_time <= current_time && is_completed[i] == false)
            {
                q.push(i);
                is_completed[i] = true;
            }
        }
        if (remaining_brust[index] > 0)
            q.push(index);

        if (q.empty())
        {
            for (unsigned int i = 1; i < processes->size(); i++)
            {
                if (remaining_brust[i] > 0)
                {
                    q.push(i);
                    is_completed[i] = true;
                    break;
                }
            }
        }
    }

    cout << "PID "
         << " Waiting time "
         << " Turn around time"
         << endl;

    int total_wt = 0, total_tat = 0;

    for (unsigned int i = 0; i < processes->size(); i++)
    {
        total_wt = total_wt + processes->at(i)->waiting_time;
        total_tat = total_tat + processes->at(i)->turnaround_time;
        cout << " " << processes->at(i)->pid << "\t" << processes->at(i)->waiting_time << "\t\t" << processes->at(i)->turnaround_time << endl;
    }

    cout << "Avg waiting time = "
         << (float)total_wt / (float)processes->size();
    cout << "\nAvg turn around time = "
         << (float)total_tat / (float)processes->size();
    cout << "\nCPU clock time = "
         << timer << endl;
}