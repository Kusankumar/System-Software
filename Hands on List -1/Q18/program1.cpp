/*
Write a program to perform Record locking.
a. Implement write lock
b. Implement read lock
Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
*/

#include<stdio.h>
#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<cstring>
#include<string>

int main(){
  const char *path="testfile.txt";
  int fd = open(path,O_RDWR | O_CREAT |O_TRUNC,0666);
  
  struct flock flk;
  flk.l_type = F_WRLCK;
  flk.l_whence = SEEK_SET;
  flk.l_start = 0;
  flk.l_len = 256;
  
  if(fcntl(fd,F_SETLK,&flk)==-1){
    std::cerr << "Failed to acquire lock: " << strerror(errno) << std::endl;
    close(fd);
    return 1;
  }
  std::cout << "Write Lock acquired"  <<std::endl;
  
  char data[64];
  ssize_t readline;
  int records =3;
  std::cout << "Enter Input lines" <<std::endl;
  while(records--){
    memset(data,0,sizeof(data));   //If we don't clear buffer and next input size is less than previous input then input will contain leftover data from previous data
    if((readline = read(STDIN_FILENO,data,sizeof(data)-1))<0){
      std::cerr << "Failed to read record number:" << strerror(errno) << std::endl;
      close(fd);
      return 1;
    }
  
    if(write(fd,data,readline)<0){
     std::cerr << "Failed to write record number:" << strerror(errno) << std::endl;
     close(fd);
      return 1; 
    }
  }
  
  std::cout << "Write Lock removed" << std::endl;
  flk.l_type = F_RDLCK;
  if(fcntl(fd,F_SETLK,&flk)==-1){
    std::cerr << "Failed to acquire read lock: " << strerror(errno) << std::endl;
    close(fd);
    return 1;
  }
  std::cout << "Read Lock acquired" << std::endl;
  
  /*records = 3;
  std::string line;
  
  while(records--){
    while((readline = read(fd,data,sizeof(data)))>0){
      for(ssize_t i = 0;i<readline;++i){
        if(data[i]=='\n'){
          std::cout << line << std::endl; 
          line="";
          
        }
        else{
            line+= data[i];
        }
      }
    }
     if (readline < 0) {
            std::cerr << "Failed to read record: " << strerror(errno) << std::endl;
            close(fd);
            return 1;
        }
  }
  */
  flk.l_type = F_UNLCK;
  if(fcntl(fd,F_SETLK,&flk)==-1){
    std::cerr << "Failed to release lock: " << strerror(errno) << std::endl;
    close(fd);
    return 1;
  }
  close(fd);
  return 0;
}
