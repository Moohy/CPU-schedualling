#ifndef PROCESS
#define PROCESS
#include <vector>
#include <iostream>
using namespace std;

struct process
{
    int pid;
    float burst_time;
    float arrival_time;
    float response_time;
    float waiting_time;
    float turnaround_time;
    float start_time;
    float completion_time;
};

#endif