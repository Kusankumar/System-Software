/*
============================================================================
Name : Q27b.c
Author : Sonu Kumar Mahto

Description--------------------------
27. Write a program to execute ls -Rl by the following system calls
a. execl
b. execlp
c. execle

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(){
    int e = execlp("ls","ls","-rl",(char *)NULL);
    if(e==-1){
        fprintf(stderr,"Error occured: %s\n",strerror(errno));
        return 1;
    }
    return 0;
}
/*=============================================================

*/
