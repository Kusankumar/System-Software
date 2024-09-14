/*
============================================================================
Name : Q11b.c
Author : Sonu Kumar Mahto

Description--------------------------
11. Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not.
a. use dup2

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<stdbool.h>

bool isfdvalid(int fd){
  if(fd<0){
    perror("Error Occure");
    return false;
  }
  return true;
}
int main(){
  const char *path = "2testfile.txt";
  
  int fd = open(path,O_RDWR | O_CREAT | O_APPEND,0666);
  if(!(isfdvalid(fd))){
    close(fd);
    return 1;
  }
  
  int newfd = 5;
  if(dup2(fd,newfd)==-1){
    fprintf(stderr,"Error allocating File descriptor: %s\n",strerror(errno));
    close(newfd);
    close(fd);
    return 1;
  }
  
  //Writing to file using old file descriptor fd
  char buffer[64];
  ssize_t byteread;
  if((byteread = read(STDIN_FILENO,buffer,sizeof(buffer)))<0){
    fprintf(stderr,"Error Reading Input from STDIN:  %s\n",strerror(errno));
    close(fd);
    close(newfd);
    return 1;
  }
  if(write(fd,buffer,byteread)<0){
    fprintf(stderr,"Error Writing to File:  %s\n",strerror(errno));
    close(fd);
    close(newfd);
    return 1;
  }
  
  //Writing to file using new file descriptor newfd
  if((byteread = read(STDIN_FILENO,buffer,sizeof(buffer)))<0){
    fprintf(stderr,"Error Reading Input from STDIN:  %s\n",strerror(errno));
    close(fd);
    close(newfd);
    return 1;
  }
  if(write(newfd,buffer,sizeof(buffer))<0){
    fprintf(stderr,"Error Writing to File:  %s\n",strerror(errno));
    close(fd);
    close(newfd);
    return 1;
  }
  printf("Old fd: %d\nNew fd: %d\n",fd,newfd);
  close(fd);
  close(newfd);
  return 0;
}

/*
$ g++ 2program.cpp -o 2main
HI, I'm Sonu Kumar mahto
I'm writing to file after fuplicating file descriptor.
Old fd: 3  New fd: 5

$ cat 2testfile.txt
HI, I'm Sonu Kumar mahto
I'm writing to file after fuplicating file descriptor.


*/
