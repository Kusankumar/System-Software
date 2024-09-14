/*
============================================================================
Name : Q7.c
Author : Sonu Kumar Mahto

Description--------------------------
7. Write a program to copy file1 into file2 ($cp file1 file2).
Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<stdbool.h>

bool isfdvalid(int fd){
  if(fd<0){
    perror("Something is wrong");
    return false;
  }
  return true;
}

int main(void){
  const char *source = "testfile.txt";
  const char *dest = "test.txt";
  
  int sfd = open(source,O_RDONLY);
  if(!isfdvalid(sfd)){
    close(sfd);
    return 1;
  }
  
  int dfd = open(dest,O_WRONLY | O_CREAT |O_APPEND,0666 );
  if(!isfdvalid(dfd)){
    close(dfd);
    return 1;
  }
  
  char buffer[512];
  ssize_t readline;
  
  while((readline = read(sfd,buffer,sizeof(buffer)))>0){
    ssize_t writeline = write(dfd,buffer,readline);
    if(readline!=writeline){
      perror("Something is wrong");
      close(sfd);
      close(dfd);
      return 1;
    }
  }
  if(!isfdvalid(readline)){
    close(sfd);
    close(dfd);
    return 1;
  }
  
  close(sfd);
  close(dfd);
  return 0;
}

