/*
============================================================================
Name : Q9.c
Author : Sonu Kumar Mahto

Description--------------------------
9. Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.

Date: 12 Sept, 2024 
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include "../Q8/myhandlers2.h"
#define PRINTSTDERROR() fprintf(stderr,"Error Occoured: %s\n",strerror(errno))

int main(){
    signal(SIGINT,handler);
    pause();

    signal(SIGINT,SIG_DFL);
    pause();
    return 0;
}
/*
Output======================================================================

============================================================================
*/