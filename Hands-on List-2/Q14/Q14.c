/*
============================================================================
Name : Q14.c
Author : Sonu Kumar Mahto

Description--------------------------
14. Write a simple program to create a pipe, write to the pipe, read from pipe
and display on the monitor.

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
    int fds[2];
    if(pipe(fds)==-1){
        PRINTSTDERROR("Error Creating Pipe");
        exit(EXIT_FAILURE);
    }
    printf("FD of read end: %d\nFD of write end: %d\n",fds[0],fds[1]);

    char buff[64]="I'm Sonu, student at IIIT B, persuing MTech in CSE";
    ssize_t bytes;
    if((bytes = write(fds[1],buff,sizeof(buff)-1))==-1){
        PRINTSTDERROR("Error Writing on pipe");
        close(fds[0]);
        close(fds[1]);
        exit(EXIT_FAILURE);
    }

    if((bytes = read(fds[0],buff,sizeof(buff)-1))==-1){
        PRINTSTDERROR("Error reading from pipe");
        close(fds[0]);
        close(fds[1]);
        exit(EXIT_FAILURE);
    }
    if(bytes>0)
        buff[bytes]='\0';
    printf("Message: %s\n",buff);

    close(fds[0]);
    close(fds[1]);
    return 0;
}
/*
Output======================================================================
$ ./Q14
FD of read end: 3
FD of write end: 4
Message: I'm Sonu, student at IIIT B, persuing MTech in CSE
============================================================================
*/