
#include "../process.h"

#ifndef FCFS_ALG
#define FCFS_ALG
#include <queue>

void startTime(process *p, process *prev_p);
void completionTime(process *p);
void turnAround(process *process);
void waitingTime(process *process);
void responseTime(process *process);
void fcfs(vector<process *> *processes);

#endif