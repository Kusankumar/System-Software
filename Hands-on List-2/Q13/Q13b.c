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

int main(){
    int p;
    scanf("%d: ",&p);
    if(kill(p,SIGSTOP)==-1){
            PRINTSTDERROR("Couldn't Perform Kill()");
            exit(EXIT_FAILURE);
    }

    if(kill(p,SIGCONT)==-1){
            PRINTSTDERROR("Couldn't Perform Kill()");
            exit(EXIT_FAILURE);
    }
    return 0;
}
/*
Output======================================================================
$ ./Q13b
36248
============================================================================
*/