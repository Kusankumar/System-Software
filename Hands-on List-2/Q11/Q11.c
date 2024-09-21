/*
============================================================================
Name : Q11.c
Author : Sonu Kumar Mahto

Description--------------------------
11. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - use sigaction system call.

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
#define PRINTSTDERROR(msg) fprintf(stderr, "%s: %s\n",msg, strerror(errno))

void handler(int signal){
    if(signal == SIGINT){
        const char msg[] = "SIGFPE Recieved\n";
        write(STDOUT_FILENO,msg,sizeof(msg)-1);
        _exit(EXIT_SUCCESS);
    }
}

int main()
{
    struct sigaction actold,actnew;
    
    memset(&actold,0,sizeof(actold));
    memset(&actnew,0,sizeof(actnew));

    sigemptyset(&actold.sa_mask);
    actold.sa_handler = SIG_IGN;
    actold.sa_flags = 0;

    sigemptyset(&actnew.sa_mask);
    actnew.sa_handler = SIG_DFL;
    actnew.sa_flags = 0;
    
    printf("PID: %d\n",getpid());
    if(sigaction(SIGINT,&actold,NULL)==-1){
        PRINTSTDERROR("Error performing sigaction");
        exit(EXIT_FAILURE);
    }
    sleep(5);

    printf("\n");
    if(sigaction(SIGINT,&actnew,NULL)==-1){
        PRINTSTDERROR("Error performing sigaction");
        exit(EXIT_FAILURE);
    }
    sleep(5);
    
    return 0;    
}
/*
Output======================================================================
$ ./Q11
PID: 17354
^C^C^C
^C
============================================================================
*/