all:
	clang++ -stdlib=libc++ -Wall -Werror -v -o app app.cpp FCFS/fcfs.cpp SJF/sjf.cpp  RR/rr.cpp 