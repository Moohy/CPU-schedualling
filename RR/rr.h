
#include "../process.h"

#ifndef RR_ALG
#define RR_ALG

// #include <iostream>
// #include <iomanip>
#include <queue>
#include <cmath>
// using namespace std;

void rr(vector<process *> *processes, int time_quantum, float context_switch);
void completionTime(process *p, float current_time);
void turnAround(process *process);
void waitingTime(process *process);
void responseTime(process *process);
void startTimeCalculation(process *p, float current_time);

#endif