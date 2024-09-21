/*
============================================================================
Name : Q17a.c
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
#define PRINTERRMSG(msg) fprintf(stderr, "%s: %s\n",msg, strerror(errno))

int main() {
    int fds[2];
    pid_t cid;

    if (pipe(fds) == -1) {
        PRINTERRMSG("Error Creating Pipe");
        exit(EXIT_FAILURE);
    }

    if ((cid = fork()) == -1) {
        PRINTERRMSG("Error Creating child");
        exit(EXIT_FAILURE);
    }

    if (cid == 0) {
        close(fds[0]);
        close(STDOUT_FILENO);

        if(dup(fds[1])==-1){
            PRINTERRMSG("Error duplicating fd");
            close(fds[1]);
            exit(EXIT_FAILURE);
        }
        if(execlp("ls", "ls", "-l", (char *)NULL)==-1){
            PRINTERRMSG("execlp() error");
            exit(EXIT_FAILURE);
        }
        close(fds[1]);
        exit(EXIT_SUCCESS);
    }else{
        sleep(2);
        close(fds[1]);
        close(STDIN_FILENO);

        if(dup(fds[0])==-1){
            PRINTERRMSG("Error duplicating fd");
            close(fds[0]);
            exit(EXIT_FAILURE);
        }
        if(execlp("wc","wc",(char*)NULL)==-1){
            PRINTERRMSG("execlp() error");
            exit(EXIT_FAILURE);
        }
        close(fds[0]);
        exit(EXIT_SUCCESS);
    }
    waitpid(cid, NULL, 0);
    return 0;
}

/*
Output======================================================================
$ ./Q17a
    7      56     345
============================================================================
*/