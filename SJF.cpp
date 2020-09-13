#include "SJF.h"

void startTime(process *p, int clock_time)
{
    // add start time to process
    p->start_time = clock_time;
}

void sjf(vector<process *> *processes)
{
    // this is for checking the completness of processes
    vector<bool> is_completed(processes->size(), false);

    // timer for a process
    int cpu_timer = 0;
    // completed processes counter
    unsigned int completed = 0;

    while (completed != processes->size())
    {
        // this is to calculate min and max
        int index = -1;
        int min = 99999999;

        for (unsigned int i = 0; i < processes->size(); i++)
        {
            // check for processes arrived now or earlier than the timer
            if (processes->at(i)->arrival_time <= cpu_timer && !is_completed[i])
            {
                // look for the shortest arrived process and save its index
                if (processes->at(i)->burst_time < min)
                {
                    min = processes->at(i)->burst_time;
                    index = i;
                }
                // if two short processes have the same burst time
                // checck for the earliest arrived job between the two and save its index
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

        // if there exists a process do the claculation
        // if not increase the timer by 1
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
         << cpu_timer << endl;
}