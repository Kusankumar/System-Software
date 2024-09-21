/*
============================================================================
Name : Q8d.c
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
    
    printf("PID: %d\n",getpid());
    signal(SIGALRM,handler);
    
    alarm(5);
    pause();

    return 0;
}
/*
Output======================================================================
$ ./Q8d
PID: 8027
SIGALRM Received

============================================================================
*/