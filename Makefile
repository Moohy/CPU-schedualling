all:
	g++  -Wall -Werror  -o app app.cpp FCFS/fcfs.cpp SJF/sjf.cpp  RR/rr.cpp 