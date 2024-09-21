/*
============================================================================
Name : Q16.c
Author : Sonu Kumar Mahto

Description--------------------------
16. Write a program to send and receive data from parent to child vice versa.
Use two way communication.

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#define PRINTSTDERROR(msg) fprintf(stderr, "%s: %s\n",msg, strerror(errno))

int main(){
    int pp1[2],pp2[2];
    pid_t par = getpid();
    

    if(pipe(pp1)==-1){
        PRINTSTDERROR("Error Creating Pipe 1");
        exit(EXIT_FAILURE);
    }
    if(pipe(pp2)==-1){
        PRINTSTDERROR("Error Creating Pipe 2");
        exit(EXIT_FAILURE);
    }

    pid_t child = fork();
    if(child==0){
        sleep(2);
        char buff[128]= "This is the message written by child\n";
        ssize_t bytes;
        if(write(pp2[1],buff,sizeof(buff)-1)==-1){
            PRINTSTDERROR("Error Writing on pipe");
            close(pp2[0]);
            close(pp2[1]);
            exit(EXIT_FAILURE);
        }
        printf("Child(%d) sends the message successfully\n",getpid());
        sleep(3);
        if((bytes = read(pp1[0],buff,sizeof(buff)-1))==-1){
            PRINTSTDERROR("Error reading from pipe");
            close(pp1[0]);
            close(pp1[1]);
            exit(EXIT_FAILURE);
        }
        if(bytes>0)
            buff[bytes]='\0';
        if(kill(par,SIGCHLD)==-1){
            PRINTSTDERROR("Error sending Signal");
            exit(EXIT_FAILURE);
        }
        printf("From Parent(%d): %s\n",par,buff);
    }
    else if(child>0) {
        ssize_t bytes;
        char buff[128]="This is the message written by Parent\n";
        if(write(pp1[1],buff,sizeof(buff)-1)==-1){
            PRINTSTDERROR("Error Writing on pipe");
            close(pp1[0]);
            close(pp1[1]);
            exit(EXIT_FAILURE);
        }
        printf("Parent(%d) sends the message successfully\n",par);
        sleep(4);

        if((bytes = read(pp2[0],buff,sizeof(buff)-1))==-1){
            PRINTSTDERROR("Error reading from pipe");
            close(pp1[0]);
            close(pp1[1]);
            exit(EXIT_FAILURE);
        }
        if(bytes>0)
            buff[bytes]='\0';
        if(waitpid(child,NULL,0)==-1){
            PRINTSTDERROR("Error executing waitpid()");
            exit(EXIT_FAILURE);
        }
        printf("From Child(%d): %s\n",par,buff);
    }
    return 0;
}
/*
Output======================================================================
$ ./Q16
Parent(10046) sends the message successfully
Child(10047) sends the message successfully
From Parent(10046): This is the message written by Parent

From Child(10046): This is the message written by child
============================================================================
*/