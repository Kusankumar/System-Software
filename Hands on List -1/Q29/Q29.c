/*
============================================================================
Name : Q29.c
Author : Sonu Kumar Mahto

Description--------------------------
29. Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO, SCHED_RR)

Date: 30th Aug, 2024.
============================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

void currPolicy(int p) {
    switch(p) {
        case SCHED_FIFO:
            printf("Current scheduling policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Current scheduling policy: SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("Current scheduling policy: SCHED_OTHER\n");
            break;
        default:
            printf("Current scheduling policy: Unknown\n");
            break;
    }
}

int main() {
    int p = sched_getscheduler(0);

    if (p == -1) {
        fprintf(stderr, "Error Occured: %s\n", strerror(errno));
        return 1;
    }
    currPolicy(p);

    int newp = SCHED_FIFO;
    struct sched_param sp;
    sp.sched_priority = 7;

    if (sched_setscheduler(0, newp, &sp) == -1) {
        fprintf(stderr, "Error Occured: %s\n", strerror(errno));
        return 1;
    }

    p = sched_getscheduler(0);
    if (p== -1) {
        fprintf(stderr, "Error Occured: %s\n", strerror(errno));
        return 1;
    }
    currPolicy(p);
    return 0;
}

/*=============================================================
$ sudo ./Q29
Current scheduling policy: SCHED_OTHER
Current scheduling policy: SCHED_FIFO
*/
