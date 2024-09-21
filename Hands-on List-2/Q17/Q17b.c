/*
============================================================================
Name : Q17b.c
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
    pid_t c1, c2;

    if (pipe(fds) == -1) {
        PRINTERRMSG("Error Creating Pipe");
        exit(EXIT_FAILURE);
    }

    if ((c1 = fork()) == -1) {
        PRINTERRMSG("Error Creating child");
        exit(EXIT_FAILURE);
    }

    if (c1 == 0) {
        dup2(fds[1], STDOUT_FILENO);
        close(fds[0]);
        close(fds[1]);

        if(execlp("ls", "ls", "-l", (char *)NULL)==-1){
            PRINTERRMSG("Error replacing with new process Image");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }

    if ((c2 = fork()) == -1) {
        PRINTERRMSG("Error Creating child");
        exit(EXIT_FAILURE);
    }
    if (c2 == 0) {
        dup2(fds[0], STDIN_FILENO);
        close(fds[1]);
        close(fds[0]);

        if(execlp("wc", "wc", (char *)NULL)==-1){
            PRINTERRMSG("Error replacing with new process Image");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_FAILURE);
    }

    close(fds[0]);
    close(fds[1]);

    waitpid(c1, NULL, 0);
    waitpid(c2, NULL, 0);

    return 0;
}

/*
Output======================================================================
$ ./Q17b
    7      56     345
============================================================================
*/