/*
============================================================================
Name : Q13.c
Author : Sonu Kumar Mahto

Description--------------------------
13. Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to verify whether the data is available within 10 seconds or not (check in $man 2 select).

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<sys/select.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>


int main(){
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO,&fds);
  
  struct timeval time;
  time.tv_sec = 10;
  time.tv_usec = 0;
  
  int tfds = select(STDIN_FILENO +1,&fds,NULL,NULL,&time);//Monitor fd from 0 to 1(excluding 1) file descriptor STDIN = 0 STDOUT = 1 STD STDERR = 2
  if(tfds==-1){
    perror("Error occur while monitoring FDs");
    return 1;
  }
  else if(tfds==0){
    printf("Time out occur\n");
  }
  else{
    if(FD_ISSET(STDIN_FILENO,&fds)==0){
      perror("Error Reading input");
    }
    else{
      char buffer[128];
      ssize_t readline = read(STDIN_FILENO,buffer,sizeof(buffer)-1);//-1 for null pointer, Else we'll get garbage if we print the string
      if(readline>0){
        buffer[readline] = '\0';
        printf("Input Data: %s",buffer);
      }
    }
    
  }
  return 0;
}

