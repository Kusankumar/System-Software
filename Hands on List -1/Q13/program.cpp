#include<iostream>
#include<sys/select.h>
#include<unistd.h>
#include<cstring>
#include<cerrno>
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
    std::cout << "Time out occur" << std::endl;
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
        std::cout << "Input Data: " << buffer << std::endl;
      }
    }
    
  }
  return 0;
}

