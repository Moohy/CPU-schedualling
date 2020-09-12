#include "fcfs.h"

void startTime(process *p, process *prev_p)
{
    // calculating start time
    if (prev_p == nullptr)
        p->start_time = p->arrival_time;
    else
        p->start_time = max(prev_p->completion_time, p->arrival_time);
}

void fcfs(vector<process *> *processes)
{
    vector<process *> p_arr;

    queue<process *> p;

    //first process
    p.push(processes->at(0));
    process *temp = p.front();
    p.pop();
    startTime(temp, nullptr);
    completionTime(temp);
    turnAround(temp);
    waitingTime(temp);
    responseTime(temp);

    p_arr.push_back(temp);

    int clock_time = processes->at(0)->burst_time;
    unsigned int i = 1;
    unsigned int counter = i;

    for (i = 1; i < clock_time; i++)
    {
        // push to queue newly arrived process
        if (counter < processes->size() && processes->at(counter)->arrival_time == i)
        {
            p.push(processes->at(counter));
            clock_time += processes->at(counter)->burst_time;
            ++counter;
            while (counter < processes->size() - 1 && processes->at(counter + 1)->arrival_time == i)
            {
                p.push(processes->at(counter));
                clock_time += processes->at(counter)->burst_time;
                ++counter;
            }
        }

        // process ended
        if (i == p_arr.back()->completion_time)
        {
            // pop front
            process *temp = p.front();
            p.pop();

            // do caculation
            startTime(temp, p_arr.back());
            completionTime(temp);
            turnAround(temp);
            waitingTime(temp);
            responseTime(temp);

            p_arr.push_back(temp);
        }
    }

    cout << "PID "
         << " Waiting time "
         << " Turn around time"
         << endl;

    int total_wt = 0, total_tat = 0;

    for (i = 0; i < processes->size(); i++)
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
         << clock_time << endl;
}