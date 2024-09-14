/*
============================================================================
Name : Q6.c
Author : Sonu Kumar Mahto

Description--------------------------
6. Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls

Date: 30th Aug, 2024.
============================================================================*/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

int main(void){
  char buffer[512];
  
  ssize_t datainp = read(STDIN_FILENO,buffer,sizeof(buffer));
  if(datainp<1){
    fprintf(stderr,"Error reading from STDIN: %s",strerror(errno));
    return 1;
  }
  
  ssize_t dataout = write(STDOUT_FILENO,buffer,datainp);
  if(dataout<1){
    fprintf(stderr,"Error writing from STDout: %s",strerror(errno));
  }
  return 0;
}
/*===================================================================
$ gcc Q6.c -o main
$ ./main
Hi how are you?
Hi how are you?
*/
