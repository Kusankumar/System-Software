/*
============================================================================
Name : Q17a.c
Author : Sonu Kumar Mahto

Description--------------------------
17. Write a program to simulate online ticket reservation. Implement write lock Write a program to open a file, store a ticket number and exit. Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main(){
  const char *path="testfile.txt";
  int fd = open(path,O_RDWR | O_CREAT,0666);
  
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
  printf("Enter a ticket number: ");
  fflush(stdout);
  
  char ticketnum[16];
  ssize_t data;
  if((data = read(STDIN_FILENO,ticketnum,sizeof(ticketnum)-1))<0){
    fprintf(stderr,"Failed to read ticket number: %s\n",strerror(errno));
    close(fd);
    return 1;
  }
  if(data>0)
    ticketnum[data] = '\0';
  
  if(write(fd,ticketnum,sizeof(ticketnum))<0){
    fprintf(stderr,"Failed to write ticket number: %s\n",strerror(errno));
    close(fd);
    return 1; 
  }
  printf("Ticket number successfully written to %s\n",path);
  
  flk.l_type = F_UNLCK;
  if(fcntl(fd,F_SETLK,&flk)==-1){
    fprintf(stderr,"Failed to release lock: %s\n",strerror(errno));
    close(fd);
    return 1;
  }
  close(fd);
  return 0;
}
