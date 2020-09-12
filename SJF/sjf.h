

#include "../process.h"

#ifndef SJF_ALG
#define SJF_ALG
#include <iomanip>

void startTime(process *p, int clock_time);
void completionTime(process *p);
void turnAround(process *process);
void waitingTime(process *process);
void responseTime(process *process);
void sjf(vector<process *> *processes);

#endif