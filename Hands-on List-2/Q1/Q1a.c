/*
============================================================================
Name : Q1a.c
Author : Sonu Kumar Mahto

Description--------------------------
1. Write a separate program (for each time domain) to set a interval timer in 10sec and
10micro second
a. ITIMER_REAL
b. ITIMER_VIRTUAL
c. ITIMER_PROF

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

void handler(int signal) {
    if (signal == SIGALRM)
        printf("SIGALRM Received\n");
    else if (signal == SIGVTALRM)
        printf("SIGVTALRM Received\n");
    else if(signal == SIGPROF)
        printf("SIGPROF Received\n");
}
int main(){
    signal(SIGALRM, handler);

    struct itimerval clk;
    clk.it_value.tv_sec = 10;           
    clk.it_value.tv_usec = 10;          
    
    clk.it_interval.tv_sec = 10;        
    clk.it_interval.tv_usec = 10;       

    if (setitimer(ITIMER_REAL, &clk, NULL) == -1) {
        fprintf(stderr,"Error Setting Up time: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    while(1)pause();

  return 0;
}

/*
Output======================================================================
$ ./a.out
SIGALRM Received
SIGALRM Received
============================================================================
*/