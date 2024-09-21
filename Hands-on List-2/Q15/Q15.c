/*
============================================================================
Name : Q15.c
Author : Sonu Kumar Mahto

Description--------------------------
15. Write a simple program to send some data from parent to the child process

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define PRINTSTDERROR(msg) fprintf(stderr, "%s: %s\n",msg, strerror(errno))

int main(){
    int fds[2];
    
    pid_t par = getpid();
    ssize_t bytes;
    char buff[128]="I'm Sonu, student at IIIT B, persuing MTech in CSE";

    if(pipe(fds)==-1){
        PRINTSTDERROR("Error Creating Pipe");
        exit(EXIT_FAILURE);
    }
    pid_t child = fork();
    if(child==0){
        sleep(5);
        if((bytes = read(fds[0],buff,sizeof(buff)-1))==-1){
            PRINTSTDERROR("Error reading from pipe");
            close(fds[0]);
            close(fds[1]);
            exit(EXIT_FAILURE);
        }
        if(bytes>0)
            buff[bytes]='\0';
        printf("Message written by Parent. PID: %d\n%s\n",par,buff);
        if(kill(par,SIGCHLD)==-1){
            PRINTSTDERROR("Error sending Signal");
            exit(EXIT_FAILURE);
        }
    }
    else if(child>0) {
        if((bytes = write(fds[1],buff,sizeof(buff)-1))==-1){
            PRINTSTDERROR("Error Writing on pipe");
            close(fds[0]);
            close(fds[1]);
            exit(EXIT_FAILURE);
        }
        printf("I'm Parent(ID: %d), writing done successfully\n",par);
        if(waitpid(child,NULL,0)==-1){
            PRINTSTDERROR("Error executing waitpid()");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
/*
Output======================================================================
$ ./Q15
I'm Parent(ID: 8006), writing done successfully
Message written by Parent. PID: 8006
I'm Sonu, student at IIIT B, persuing MTech in CSE
============================================================================
*/