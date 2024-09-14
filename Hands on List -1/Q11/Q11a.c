/*
============================================================================
Name : Q11a.c
Author : Sonu Kumar Mahto

Description--------------------------
11. Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not.
a. use dup

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
  const char *path = "1testfile.txt";
  
  int fd = open(path,O_RDWR | O_CREAT | O_APPEND,0666);
  if(!(isfdvalid(fd))){
    close(fd);
    return 1;
  }
  
  int newfd = dup(fd);
  if(!(isfdvalid(newfd))){
    close(newfd);
    close(fd);
    return 1;
  }
  
  //Writing to file using old file descriptor fd
  char buffer[64];
  ssize_t byteread;
  if((byteread = read(STDIN_FILENO,buffer,sizeof(buffer)))<0){
    fprintf(stderr,"Error Reading Input from STDIN: %s\n",strerror(errno));
    close(fd);
    close(newfd);
    return 1;
  }
  if(write(fd,buffer,byteread)<0){
    fprintf(stderr,"Error Writing to File: %s\n",strerror(errno));
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
    fprintf(stderr,"Error Writing to File: %s\n",strerror(errno));
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
$ g++ 1program.cpp -o 1main

$ ./1main
Hi my name is Sonu Kumar Mahto
I'm Student at IIITB persuing my Masters in CS

$ cat testfile.txt
Hi my name is Sonu Kumar Mahto
I'm Student at IIITB persuing my Masters in CS

*/



/*
int dup(int oldfd);--------------------------------------------------------------
The  dup()  system  call  allocates a new file descriptor that refers to the same
       open file description as the descriptor oldfd. The new file descriptor number is guaranteed to be
       the lowest-numbered file descriptor that was unused in the calling process.

int dup2(int oldfd, int newfd);
The dup2() system call performs the same task as dup(), but instead of using  the
       lowest-numbered unused file descriptor, it uses the file descriptor number speci‐
       fied in newfd.  In other words, the file descriptor newfd is adjusted so that  it
       now refers to the same open file description as oldfd.

       If  the  file  descriptor  newfd  was  previously open, it is closed before being
       reused; the close is performed silently (i.e., any errors during  the  close  are
       not reported by dup2()).
*/
