/*
============================================================================
Name : Q8b.c
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

int main(){
    int arr[10];
    int indx=0;
    
    printf("PID: %d\n",getpid());
    signal(SIGINT,handler);
    
    while (1);
    
    return 0;
}
/*
Output======================================================================
./Q8b
PID: 6338
^C
SIGINT Received
^C
SIGINT Received
============================================================================
*/