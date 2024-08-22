#include<iostream>
#include<unistd.h>
#include<cstring>
#include<cerrno>

int main(void){
  char buffer[512];
  
  ssize_t datainp = read(STDIN_FILENO,buffer,sizeof(buffer));
  if(datainp<1){
    std::cerr << "Error reading from STDIN: " << strerror(errno) << std::endl;
    return 1;
  }
  
  ssize_t dataout = write(STDOUT_FILENO,buffer,datainp);
  if(dataout<1){
    std::cerr << "Error writing to STDOUT: " << strerror(errno) << std::endl;
  }
  return 0;
}
