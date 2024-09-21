/*
============================================================================
Name : Q23.c
Author : Sonu Kumar Mahto

Description--------------------------
23. Write a program to print the maximum number of files can be opened within 
a process and size of a pipe (circular buffer).

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>

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
    printf("\nOPEN_MAX: %ld\n",systemConfg(_SC_OPEN_MAX));
    printf("\nPIPE SIZE: %ld\n",pathconf(".",_PC_PIPE_BUF));
    return 0;
}
/*
Output======================================================================
$  ./Q23

OPEN_MAX: 1024
PIPE SIZE: 4096
============================================================================
*/