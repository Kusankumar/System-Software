#include<iostream>
#include<unistd.h>
#include<cstring>
#include<cerrno>
#include<fcntl.h>

bool isfdvalid(int fd){
  if(fd<0){
    perror("Error Occure");
    return false;
  }
  return true;
}
int main(){
  const char *path = "3testfile.txt";
  
  int fd = open(path,O_RDWR | O_CREAT | O_APPEND,0666);
  if(!(isfdvalid(fd))){
    close(fd);
    return 1;
  }
  
  int newfd = fcntl(fd,F_DUPFD,5);
  if(!(isfdvalid(newfd))){
    close(newfd);
    close(fd);
    return 1;
  }
  
  //Writing to file using old file descriptor fd
  char buffer[64];
  ssize_t byteread;
  if((byteread = read(STDIN_FILENO,buffer,sizeof(buffer)))<0){
    std::cerr << "Error Reading Input from STDIN: " << strerror(errno) << std::endl;
    close(fd);
    close(newfd);
    return 1;
  }
  if(write(fd,buffer,byteread)<0){
    std::cerr << "Error Writing to File: " << strerror(errno) << std::endl;
    close(fd);
    close(newfd);
    return 1;
  }
  
  //Writing to file using new file descriptor newfd
  if((byteread = read(STDIN_FILENO,buffer,sizeof(buffer)))<0){
    std::cerr << "Error Reading Input from STDIN: " << strerror(errno) << std::endl;
    close(fd);
    close(newfd);
    return 1;
  }
  if(write(newfd,buffer,sizeof(buffer))<0){
    std::cerr << "Error Writing to File: " << strerror(errno) << std::endl;
    close(fd);
    close(newfd);
    return 1;
  }
  std::cout << "Old fd: " << fd << "  New fd: " << newfd << std::endl;
  close(fd);
  close(newfd);
  return 0;
}

/*

fcntl()  performs one of the operations described below on the open file descrip‐
       tor fd.  The operation is determined by cmd
       
F_DUPFD (int)
              Duplicate the file descriptor fd using the lowest-numbered available  file
              descriptor  greater than or equal to arg.  This is different from dup2(2),
              which uses exactly the file descriptor specified.

              On success, the new file descriptor is returned.
*/
