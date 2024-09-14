/*
============================================================================
Name : Q15.c
Author : Sonu Kumar Mahto

Description--------------------------
15. Write a program to display the environmental variable of the user (use environ).

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
extern char **environ;

int main(void){
  char **env = environ;
  while(*env!=NULL){
    printf("%s \n",*env++); 
  }
  return 0;
}
