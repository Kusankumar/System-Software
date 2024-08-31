/*
============================================================================
Name : Q12.c
Author : Sonu Kumar Mahto

Description--------------------------
12. Write a program to find out the opening mode of a file. Use fcntl.

Date: 30th Aug, 2024.
============================================================================*/
#include<iostream>
#include<unistd.h>
#include<cstring>
#include<cerrno>
#include<fcntl.h>

int main(){
  const char *path = "testfile.txt";
  
  int fd = open(path,O_RDWR | O_CREAT,0666);
  if(fd ==-1){
    perror("Error opening File");
    close(fd);
    return 1;
  }
  
  int status = fcntl(fd,F_GETFL,5);//args: 5 ignored here
  if(status<0){
    close(fd);
    return 1;
  }
  
  if ((status & O_ACCMODE)==O_RDONLY) //O_ACCMODE => 00000011 so after doing & it keeps 1st 2 bit of access mode and turn off remaining bits 
    std::cout << "Access mode of " << path << " : O_RDONLY" << std::endl;
  else if((status & O_ACCMODE)==O_WRONLY)
    std::cout << "Access mode of " << path << " : WRONLY" << std::endl;
  else if((status & O_ACCMODE)==O_RDWR)
    std::cout << "Access mode of " << path << " : RDWR" << std::endl;
    
  close(fd);
  return 0;
}

/*
F_GETFL (void)
              Return (as the function result) the file access mode and the  file  status
              flags; like: 00101010 => but only 2 bits are use to define access mode.
*/
