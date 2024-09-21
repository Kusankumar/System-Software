/*
============================================================================
Name : Q5.c
Author : Sonu Kumar Mahto

Description--------------------------
5. Write a program to print the system limitation of
a. maximum length of the arguments to the exec family of functions.
b. maximum number of simultaneous process per user id.
c. number of clock ticks (jiffy) per second.
d. maximum number of open files
e. size of a page
f. total number of pages in the physical memory
g. number of currently available pages in the physical memory

Date: 12 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

long systemConfg(int name){
    errno = 0;
    long res;
    if((res = sysconf(name))==-1){
        if(errno!=0){
            fprintf(stderr,"Error on Getting System Configuration: %s",strerror(errno));
            exit(EXIT_FAILURE);
        }
        else return res;
    }
    return res;
}
int main(){
    printf("\nARG_MAX: %ld\n",systemConfg(_SC_ARG_MAX));
    printf("\nCHILD_MAX: %ld\n",systemConfg(_SC_CHILD_MAX));
    printf("\nClock ticks: %ld\n",systemConfg(_SC_CLK_TCK));
    printf("\nOPEN_MAX: %ld\n",systemConfg(_SC_OPEN_MAX));
    printf("\nPAGESIZE: %ld\n",systemConfg(_SC_PAGESIZE));
    printf("\nTotal Pages in MM: %ld\n",systemConfg(_SC_PHYS_PAGES));
    printf("\nCurrenlty Available Pages in MM: %ld\n",systemConfg(_SC_AVPHYS_PAGES));
    return 0;
}
/*
Output======================================================================
ARG_MAX: 2097152

CHILD_MAX: 30018

Clock ticks: 100

OPEN_MAX: 1048576

PAGESIZE: 4096

Total Pages in MM: 1939926

Currenlty Available Pages in MM: 38123
============================================================================
*/