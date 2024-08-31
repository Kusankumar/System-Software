/*
============================================================================
Name : Q25a.c
Author : Sonu Kumar Mahto

Description--------------------------
25. Write a program to create three child processes. The parent should wait for a particular child (use waitpid system call).

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
extern char **environ;

int main(){
  int e = execl("hello","./hello",(char *)NULL);
  if(e==-1){
    fprintf(stderr,"Error Occure: %s\n",strerror(errno));
    return 1;
  }
  printf("This should not be printed\n");
  return 0;
}
