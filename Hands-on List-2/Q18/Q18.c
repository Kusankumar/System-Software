/*
============================================================================
Name : Q18.c
Author : Sonu Kumar Mahto

Description--------------------------
18. Write a program to find out total number of directories on the pwd.
execute ls -l | grep ^d | wc ? Use only dup2.

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define PRINTERRMSG(msg) perror(msg)

int main() {
    int pipe1[2];
    int pipe2[2];
    pid_t c1,c2,c3;

    if (pipe(pipe1) == -1) {
        PRINTERRMSG("Error creating pipe1");
        exit(EXIT_FAILURE);
    }

    c1 = fork();
    if (c1 < 0) {
        PRINTERRMSG("Error forking child1");
        exit(EXIT_FAILURE);
    }

    if (c1 == 0) {
        if (dup2(pipe1[1], STDOUT_FILENO) == -1) {
            PRINTERRMSG("Error duplicating fd");
            exit(EXIT_FAILURE);
        }

        close(pipe1[0]);
        close(pipe1[1]);

        execlp("ls", "ls", "-l", (char *)NULL);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe2) == -1) {
        PRINTERRMSG("Error creating pipe2");
        exit(EXIT_FAILURE);
    }
    pipe(pipe2);
    c2 = fork();
    if (c2 < 0) {
        PRINTERRMSG("Error forking child2");
        exit(EXIT_FAILURE);
    }

    if (c2 == 0) {
        if (dup2(pipe1[0], STDIN_FILENO) == -1) {
            PRINTERRMSG("Error duplicating fd");
            exit(EXIT_FAILURE);
        }
        if (dup2(pipe2[1], STDOUT_FILENO) == -1) {
            PRINTERRMSG("Error duplicating fd");
            exit(EXIT_FAILURE);
        }
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);

        execlp("grep", "grep", "^d", (char *)NULL);
        exit(EXIT_FAILURE);
    }

    close(pipe1[0]);
    close(pipe1[1]);

    c3 = fork();
    if (c3 < 0) {
        PRINTERRMSG("Error forking child3");
        exit(EXIT_FAILURE);
    }

    if (c3 == 0) {
        if (dup2(pipe2[0], STDIN_FILENO) == -1) {
            PRINTERRMSG("Error duplicating fd");
            exit(EXIT_FAILURE);
        }
        close(pipe2[0]);
        close(pipe2[1]);

        execlp("wc", "wc", (char *)NULL);
        exit(EXIT_FAILURE);
    }
    close(pipe2[0]);
    close(pipe2[1]);

    waitpid(c1, NULL, 0);
    waitpid(c2, NULL, 0);
    waitpid(c3, NULL, 0);
    return 0;
}
/*Output======================================================================
$ ./Q18
    18     162     963
==============================================================================
*/