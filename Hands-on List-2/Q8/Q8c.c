/*
============================================================================
Name : Q8c.c
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
    if(argc!=3){
        fprintf(stderr, "Usage: \n%s <input1> <input2>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("PID: %d\n",getpid());
    signal(SIGFPE,handler);
    
    int n1,n2;
    n1 = atoi(argv[1]);
    n2 = atoi(argv[2]);
    printf("%d \n",(n1/n2));
    return 0;
}
/*
Output======================================================================
$ ./Q8c 10 0
PID: 7154
SIGFPE Received

============================================================================
*/