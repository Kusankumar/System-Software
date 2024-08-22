//Write a program to open a file in read only mode, read line by line and display each line as it is read.
//Close the file when end of file is reached.

#include<iostream>
#include<unistd.h>
#include<cerrno>
#include<cstring>
#include<fcntl.h>

bool isfdvalid(int fd){
  if(fd<0){
    perror("Something is wrong");
    return false;
  }
  return true;
}

int main(void){
  int fd = open("testfile.txt",O_RDONLY);
  if(!isfdvalid(fd)){
    close(fd);
    return 1;
  }
  
  int linecount =1;
  char buffer[100];
  ssize_t readline;
  while((readline = read(fd,buffer,sizeof(buffer)))>0){
    printf("\nLine no %d--------------------------- \n",linecount++);
    ssize_t writeline = write(STDOUT_FILENO,buffer,readline);
    if(readline!=writeline){
      perror("Something is wrong");
      close(fd);
      return 1;
    }
    printf("\n");
  }
  close(fd);
  return 0;
}
