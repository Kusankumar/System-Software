/*
============================================================================
Name : Q30.c
Author : Sonu Kumar Mahto

Description--------------------------
30. Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory

Date: 15 Sept, 2024
============================================================================
*/
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#define PRINTSTDERROR(msg) fprintf(stderr, "%s: %s\n",msg, strerror(errno))

int main(){

    return 0;
}
/*
Output======================================================================

============================================================================
*/

