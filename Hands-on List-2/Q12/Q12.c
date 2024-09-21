/*
============================================================================
Name : Q12.c
Author : Sonu Kumar Mahto

Description--------------------------
12. Write a program to create an orphan process. Use kill system call to send 
SIGKILL signal to the parent process from the child process

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
    pid_t p1 = getpid();
    pid_t c1 = fork();

    if(c1<0){
        PRINTSTDERROR("Failed to Create Child");
        exit(EXIT_FAILURE);
    }
    if(c1==0){
        printf("Child Process trying to send SIGKILL\n");
        sleep(5);
        if(kill(p1,SIGKILL)==-1){
            PRINTSTDERROR("Couldn't Perform Kill()");
            exit(EXIT_FAILURE);
        }
        printf("\nChild: %d successfully become Orphan\n",getpid());
        int i=0;
        while ((i++)<15){
            printf("hola");
            sleep(1);
        }
    }
    else{
        int i=50;
        while ((i--)>0){
            sleep(1);
            printf("I'm parent with ID: %d\n",p1);
        }
        printf("Failed to create Orphan process if this line is getting printed\n");
    }
    return 0;
}
/*
Output======================================================================
$ ./Q12
Child Process trying to send SIGKILL
I'm parent with ID: 20558
I'm parent with ID: 20558
I'm parent with ID: 20558
I'm parent with ID: 20558

Child: 20559 successfully become Orphan
============================================================================
*/