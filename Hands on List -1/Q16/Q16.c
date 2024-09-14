/*
============================================================================
Name : Q16.c
Author : Sonu Kumar Mahto

Description--------------------------
16. Write a program to perform mandatory locking.
a. Implement write lock
b. Implement read lock

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main(){
  const char *path="testfile.txt";
  int fd = open(path,O_RDWR,0666);
  
  struct flock flk;
  flk.l_type = F_WRLCK;
  flk.l_whence = SEEK_SET;
  flk.l_start = 0;
  flk.l_len = 0;
  
  if(fcntl(fd,F_SETLK,&flk)==-1){
    fprintf(stderr,"Failed to acquire lock: %s\n",strerror(errno));
    close(fd);
    return 1;
  }
  printf("Write Lock acquired\n");
  sleep(3);
  
  printf("Read Lock acquired\n");
  flk.l_type = F_RDLCK;
  if(fcntl(fd,F_SETLK,&flk)==-1){
    fprintf(stderr,"Failed to real lock: %s\n",strerror(errno));
    close(fd);
    return 1;
  }
  flk.l_type = F_UNLCK;
  if(fcntl(fd,F_SETLK,&flk)==-1){
    fprintf(stderr,"Failed to release lock: %s\n",strerror(errno));
    close(fd);
    return 1;
  }
  printf("Lock released successfully\n");
  close(fd);
  return 0;
}
