/*
============================================================================
Name : Q2.c
Author : Sonu Kumar Mahto

Description--------------------------
4. Write a program to open an existing file with read write mode. Try O_EXCL flag also

Date: 30th Aug, 2024.
============================================================================*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(void){
  char *path = "testfile.txt";
  int fd = open(path,O_RDWR);
  if(fd==-1){
    perror("File can't be open: ");
    return -1;
  }
  printf("File opened using open() function and O_RDWR flag\n File Descriptor: %d\n",fd);
  
  fd = open(path,O_RDWR | O_EXCL);
  if(fd==-1){
    perror("File can't be open using O_EXCL: ");
    return -1;
  }  
  printf("File opened using open() function and O_RDWR | O_EXCL flag\n File Descriptor: %d\n",fd);
  close(fd);
  return 0;
}
/*============================================================================
 $ gcc Q4.c -o main
 $ ./main
 File opened using open() function and O_RDWR flag
 File Descriptor: 3
 File opened using open() function and O_RDWR | O_EXCL flag
 File Descriptor: 4

*/
