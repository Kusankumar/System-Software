#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<cstring>

int main(void){
  char *path = "testfile.txt";
  int fd = open(path,O_RDWR);
  if(fd==-1){
    perror("File can't be open: ");
    return -1;
  }
  printf("File opened using open() function and O_RDWR flag\n File Descriptor: %d\n",fd);
  
  fd = open(path,O_RDWR | O_CREAT | O_EXCL);
  if(fd==-1){
    perror("File can't be open using O_EXCL: ");
    return -1;
  }  
  printf("File opened using open() function and O_RDWR | O_EXCL flag\n File Descriptor: %d\n",fd);
  close(fd);
  return 0;
}
/*
O_EXCL: Ensure that this call creates the file: if this flag is specified in con‐
              junction with O_CREAT, and pathname already exists, then open() fails with
              the error EEXIST.
*/
