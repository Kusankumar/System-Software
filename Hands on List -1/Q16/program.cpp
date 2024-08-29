#include<stdio.h>
#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<cstring>

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
  sleep(3);
  
  std::cout << "Read Lock acquired"  <<std::endl;
  flk.l_type = F_RDLCK;
  if(fcntl(fd,F_SETLK,&flk)==-1){
    std::cerr << "Failed to real lock: " << strerror(errno) << std::endl;
    close(fd);
    return 1;
  }
  flk.l_type = F_UNLCK;
  if(fcntl(fd,F_SETLK,&flk)==-1){
    std::cerr << "Failed to release lock: " << strerror(errno) << std::endl;
    close(fd);
    return 1;
  }
  std::cout << "Lock released successfully" << std::endl;
  close(fd);
  return 0;
}
