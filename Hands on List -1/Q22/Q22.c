/*
============================================================================
Name : Q22.c
Author : Sonu Kumar Mahto

Description--------------------------
22. Write a program, open a file, call fork, and then write to the file by both the child as well as the parent processes. Check output of the file

Date: 30th Aug, 2024.
============================================================================*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<stdbool.h>

bool isfdvalid(int fd){
  if(fd<0){
    perror("Something went wring ");
    return false;
  }
  return true;
}

int main(){
  const char *path = "testfile.txt";
  int fd = open(path,O_RDWR | O_CREAT | O_APPEND,0666);
  if(!isfdvalid(fd)){
    close(fd);
    return 1;
  }
  
  pid_t cp = fork();
  if(cp==-1){
    fprintf(stderr,"Failed to create Child Process: %s\n",strerror(errno));
    return 1;
  }
  
  //Writing using Parent Process-----------------------------------------------------------
  if(cp!=0){
    const char *d1="Hi I'm sonu kumar mahto, student at IIITB, persuing my Mtech in CSE\n";
    
    if(write(fd,d1,strlen(d1))<0){
      fprintf(stderr,"couldn't write using Parent Process: %s\n",strerror(errno));
      close(fd);
      return 1;
    }
  }
  //Writing using Child Process----------------------------------------------------------
  if(cp == 0){
    const char *d2="2nd,Hi I'm sonu kumar mahto, student at IIITB, persuing my Mtech in CSE\n";
    if(write(fd,d2,strlen(d2))<0){
      fprintf(stderr,"couldn't write using child Process: %s\n",strerror(errno));
      close(fd);
      return 1;
    }
  }
  
  close(fd);
  return 0;
}

/*=============================================================================================
Output:
$ cat testfile.txt
Hi I'm sonu kumar mahto, student at IIITB, persuing my Mtech in CSE
2nd,Hi I'm sonu kumar mahto, student at IIITB, persuing my Mtech in CSE

*/
