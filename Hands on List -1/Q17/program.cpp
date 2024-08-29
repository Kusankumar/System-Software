#include<stdio.h>
#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<cstring>

int main(){
  const char *path="testfile.txt";
  int fd = open(path,O_RDWR | O_CREAT,0666);
  
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
  std::cout << "Enter a ticket number: "<< std::flush ;
  
  char ticketnum[16];
  ssize_t data;
  if((data = read(STDIN_FILENO,ticketnum,sizeof(ticketnum)-1))<0){
    std::cerr << "Failed to read ticket number:" << strerror(errno) << std::endl;
    close(fd);
    return 1;
  }
  if(data>0)
    ticketnum[data] = '\0';
  
  if(write(fd,ticketnum,sizeof(ticketnum))<0){
    std::cerr << "Failed to write ticket number:" << strerror(errno) << std::endl;
    close(fd);
    return 1; 
  }
  std::cout << "Ticket number successfully written to "<< path << std::endl;
  
  flk.l_type = F_UNLCK;
  if(fcntl(fd,F_SETLK,&flk)==-1){
    std::cerr << "Failed to release lock: " << strerror(errno) << std::endl;
    close(fd);
    return 1;
  }
  close(fd);
  return 0;
}
