/*
============================================================================
Name : Q12.c
Author : Sonu Kumar Mahto

Description--------------------------
12. Write a program to find out the opening mode of a file. Use fcntl.

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
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
    printf("Access mode of %s : O_RDONLY\n",path);
  else if((status & O_ACCMODE)==O_WRONLY)
    printf("Access mode of %s : WRONLY\n",path);
  else if((status & O_ACCMODE)==O_RDWR)
    printf("Access mode of %s : RDWR\n",path);
  close(fd);
  return 0;
}

/*
F_GETFL (void)
              Return (as the function result) the file access mode and the  file  status
              flags; like: 00101010 => but only 2 bits are use to define access mode.
*/
