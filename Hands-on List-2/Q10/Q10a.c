/*
============================================================================
Name : Q10a.c
Author : Sonu Kumar Mahto

Description--------------------------
10. Write a separate program using sigaction system call to catch the following signals.
a. SIGSEGV
b. SIGINT
c. SIGFPE

Date: 15 Sept, 2024 
============================================================================
*/
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include "../Q8/myhandlers.h"
#define PRINTSTDERROR() fprintf(stderr, "Error Occurred: %s\n", strerror(errno))

int main()
{
    struct sigaction act;
    
    memset(&act,0,sizeof(act));
    sigemptyset(&act.sa_mask);

    act.sa_handler = handler;
    act.sa_flags = 0;
    
    printf("PID: %d\n",getpid());
    if(sigaction(SIGINT,&act,NULL)==-1){
        PRINTSTDERROR();
        exit(EXIT_FAILURE);
    }
    
    while(1)pause();
    
    return 0;    
}

/*
Output======================================================================
$ ./Q10a 
^C SIGINT Recieved
^C SIGINT Recieved
^C SIGINT Recieved
============================================================================
*/