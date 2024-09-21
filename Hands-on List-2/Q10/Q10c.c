/*
============================================================================
Name : Q10c.c
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
#define PRINTSTDERROR(msg) fprintf(stderr, "%s: %s\n",msg, strerror(errno))

void handler(int signal){
    if(signal == SIGFPE){
        const char msg[] = "SIGFPE Recieved\n";
        write(STDOUT_FILENO,msg,sizeof(msg)-1);
        _exit(EXIT_SUCCESS);
    }
}

int main(int argc,char* argv[])
{
    if(argc!=3){
        fprintf(stderr,"%s <input1> <input2>\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    int n1,n2;
    struct sigaction act;
    
    memset(&act,0,sizeof(act));
    sigemptyset(&act.sa_mask);

    act.sa_handler = handler;
    act.sa_flags = 0;
    
    n1 = atoi(argv[1]);
    n2 = atoi(argv[2]);

    printf("PID: %d\n",getpid());
    if(sigaction(SIGFPE,&act,NULL)==-1){
        PRINTSTDERROR("Error Performing sigaction");
        exit(EXIT_FAILURE);
    }
    sleep(2);
    int test = n1/n2;

    return 0;;
}

/*
Output======================================================================
$ ./Q10b
PID: 14056
SIGSEGV Recieved
============================================================================
*/