/*
============================================================================
Name : Q17b.c
Author : Sonu Kumar Mahto

Description--------------------------
17. Write a program to simulate online ticket reservation. Implement write lock Write a program to open a file, store a ticket number and exit. Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<cstring>
#include<string>

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
    std::cerr << "Failed to acquire lock: " << strerror(errno) << std::endl;
    close(fd);
    return 1;
  }
  std::cout << "Write Lock acquired"  <<std::endl;
  
  char ticketnum[16];
  ssize_t data;
  if((data = read(fd,ticketnum,sizeof(ticketnum)-1))<0){
    std::cerr << "Failed to read ticket number:" << strerror(errno) << std::endl;
    close(fd);
    return 1;
  }

  ticketnum[data]='\0';
  std::cout << "New Ticket Number: "<<  std::stol(ticketnum)+1 << std::endl;
  
  flk.l_type = F_UNLCK;
  if(fcntl(fd,F_SETLK,&flk)==-1){
    std::cerr << "Failed to release lock: " << strerror(errno) << std::endl;
    close(fd);
    return 1;
  }
  close(fd);
  return 0;
}
