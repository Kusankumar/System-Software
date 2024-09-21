/*
============================================================================
Name : Q17c.c
Author : Sonu Kumar Mahto

Description--------------------------
17. Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define PRINTERRMSG(msg) fprintf(stderr, "%s: %s\n",msg, strerror(errno))

int main() {
    int pipefd[2]; 
    pid_t cid;

    if(pipe(pipefd)==-1){
        PRINTERRMSG("Error Creating Pipe");
        exit(EXIT_FAILURE);
    }

    cid = fork();
    if(cid==-1){
        PRINTERRMSG("fork() Error");
        exit(EXIT_FAILURE);
    }

    if (cid == 0) {        
        close(pipefd[0]);   
        close(STDOUT_FILENO);

        if(fcntl(pipefd[1],F_DUPFD,STDOUT_FILENO)==-1){
            PRINTERRMSG("fcntl() execution error");
            exit(EXIT_FAILURE);
        }
        if(execlp("ls", "ls", "-l", NULL)==-1){
            PRINTERRMSG("execlp() error");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
        exit(EXIT_SUCCESS);

    }else {
        sleep(1);
        close(pipefd[1]);
        close(STDIN_FILENO);

        if(fcntl(pipefd[0],F_DUPFD,STDIN_FILENO)==-1){
            PRINTERRMSG("fcntl() execution error");
            exit(EXIT_FAILURE);
        }
        if(execlp("wc", "wc", NULL)==-1){
            PRINTERRMSG("execlp() error");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    }
    waitpid(cid, NULL, 0);
    return 0;
}
/*
Output======================================================================
$ ./Q17c
    7      56     345
============================================================================
*/