/*
============================================================================
Name : Q8.c
Author : Sonu Kumar Mahto

Description--------------------------
8. Write a program to open a file in read only mode, read line by line and display each line as it is read.
Close the file when end of file is reached.

Date: 30th Aug, 2024.
============================================================================*/


#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<stdbool.h>

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

/*=========================================================================
$ gcc Q8.c -o main
$ ./main
Line no 1--------------------------- 
Hi there! my name is sonu. I'm trying to solve some problem which is difficult af -_-

When Subaru N

Line no 2--------------------------- 
atsuki leaves the convenience store, the last thing he expects is to be wrenched from his everyday l

Line no 3--------------------------- 
ife and dropped into a fantasy world.
Things are not looking good for the bewildered teenager; howev

Line no 4--------------------------- 
er, not long after his arrival, he is attacked by some thugs. Armed with only a bag of
groceries and

Line no 5--------------------------- 
 a now useless cell phone, he is quickly beaten to a pulp. Fortunately, a mysterious beauty named Sa

*/
