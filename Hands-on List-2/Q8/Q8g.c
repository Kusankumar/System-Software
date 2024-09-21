/*
============================================================================
Name : Q8g.c
Author : Sonu Kumar Mahto

Description--------------------------
8. Write a separate program using signal system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE
d. SIGALRM (use alarm system call)
e. SIGALRM (use setitimer system call)
f. SIGVTALRM (use setitimer system call)
g. SIGPROF (use setitimer system call)

Date: 12 Sept, 2024 
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include "myhandlers.h"

int main(int argc,char* argv[]){
    struct itimerval timer;
    
    printf("PID: %d\n",getpid());
    signal(SIGPROF,handler);
    
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 5;
    
    timer.it_interval.tv_sec=0;
    timer.it_interval.tv_usec = 0;

    if(setitimer(ITIMER_PROF,&timer,NULL)==-1){
        fprintf(stderr,"Error Setting up Timer: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    while(1);
    return 0;
}
/*
Output======================================================================
$ ./Q8g
PID: 10538
SIGPROF Received

============================================================================
*/