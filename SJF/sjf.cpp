#include "sjf.h"

void startTime(process *p, int clock_time)
{
    p->start_time = clock_time;
}

void sjf(vector<process *> *processes)
{

    vector<bool> is_completed(processes->size(), false);

    int cpu_timer = 0;
    unsigned int completed = 0;

    while (completed != processes->size())
    {
        int index = -1;
        int min = 99999999;
        for (unsigned int i = 0; i < processes->size(); i++)
        {
            if (processes->at(i)->arrival_time <= cpu_timer && !is_completed[i])
            {
                if (processes->at(i)->burst_time < min)
                {
                    min = processes->at(i)->burst_time;
                    index = i;
                }
                if (processes->at(i)->burst_time == min)
                {
                    if (processes->at(i)->arrival_time < processes->at(index)->arrival_time)
                    {
                        min = processes->at(i)->burst_time;
                        index = i;
                    }
                }
            }
        }

        if (index != -1)
        {
            startTime(processes->at(index), cpu_timer);
            completionTime(processes->at(index));
            turnAround(processes->at(index));
            waitingTime(processes->at(index));
            responseTime(processes->at(index));

            is_completed[index] = true;
            completed++;
            cpu_timer = processes->at(index)->completion_time;
        }
        else
        {
            cpu_timer++;
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
         << cpu_timer << endl;
}