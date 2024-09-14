/*
============================================================================
Name : Q28.c
Author : Sonu Kumar Mahto

Description--------------------------
28. Write a program to get maximum and minimum real time priority.

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include <sched.h>
#include <errno.h>
#include <string.h>

int main() {
    
    int maxpr = sched_get_priority_max(SCHED_FIFO);
    int minpr = sched_get_priority_min(SCHED_FIFO);

    if (maxpr == -1 || minpr == -1) {
        fprintf(stderr, "Error occured: %s\n", strerror(errno));
        return 1;
    }

    printf("Maximum Real-time Priority: %d\n", maxpr);
    printf("Minimum Real-time Priority: %d\n", minpr);

    return 0;
}
/*=============================================================
$ ./Q28
Maximum Real-time Priority: 99
Minimum Real-time Priority: 1

*/
