/*
============================================================================
Name : Q13.c
Author : Sonu Kumar Mahto

Description--------------------------
13. Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#define PRINTSTDERROR(msg) fprintf(stderr, "%s: %s\n",msg, strerror(errno))

void handler(int signum){
    if(signum == SIGCONT){
        const char msg[]="SIGCONT Recieved Successfully\n";
        write(STDOUT_FILENO,msg,sizeof(msg)-1);
    }
}
int main(){
    printf("Process ID: %d\n",getpid());

    signal(SIGSTOP,handler);
    signal(SIGCONT,handler);
    sleep(10);
    printf("I got printed that means It works successfully\n");

    return 0;
}
/*
Output======================================================================
$ ./Q13a
36248
SIGCONT Recieved Successfully
I got printed that means It works successfully
============================================================================
*/