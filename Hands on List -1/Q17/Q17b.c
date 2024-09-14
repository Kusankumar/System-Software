/*
============================================================================
Name : Q17b.c
Author : Sonu Kumar Mahto

Description--------------------------
17. Write a program to simulate online ticket reservation. Implement write lock Write a program to open a file, store a ticket number and exit. Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

/*
Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
*/
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
  
  char ticketnum[16];
  ssize_t data;
  if((data = read(fd,ticketnum,sizeof(ticketnum)-1))<0){
    fprintf(stderr,"Failed to read ticket number: %s\n",strerror(errno));
    close(fd);
    return 1;
  }

  ticketnum[data]='\0';
  printf("New Ticket Number: %ld \n",atol(ticketnum)+1);
  
  flk.l_type = F_UNLCK;
  if(fcntl(fd,F_SETLK,&flk)==-1){
    fprintf(stderr,"Failed to release lock: %s\n",strerror(errno));
    close(fd);
    return 1;
  }
  close(fd);
  return 0;
}
