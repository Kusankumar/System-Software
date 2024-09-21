/*
============================================================================
Name : Q10b.c
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
#define PRINTSTDERROR() fprintf(stderr, "Error Occurred: %s\n", strerror(errno))

void handler(int signal){
    if(signal == SIGSEGV){
        const char msg[] = "SIGSEGV Recieved\n";
        write(STDOUT_FILENO,msg,sizeof(msg)-1);
        _exit(EXIT_SUCCESS);
    }
}
int main()
{
    struct sigaction act;
    
    memset(&act,0,sizeof(act));
    sigemptyset(&act.sa_mask);

    act.sa_handler = handler;
    act.sa_flags = 0;
    
    printf("PID: %d\n",getpid());
    if(sigaction(SIGSEGV,&act,NULL)==-1){
        PRINTSTDERROR();
        exit(EXIT_FAILURE);
    }
    int *ptr;
    sleep(2);
    *ptr=10;

    return 0;;
}

/*
Output======================================================================
$ ./Q10b
PID: 14056
SIGSEGV Recieved
============================================================================
*/